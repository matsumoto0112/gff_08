// Fill out your copyright notice in the Description page of Project Settings.

#include "LapCounter.h"

#include "gff_08/stage/RaceManager.h"
#include "gff_08/utils/MyGameInstance.h"
#include "gff_08/utils/NetworkConnectUtility.h"
#include "kismet/GamePlayStatics.h"

#include <numeric>

namespace {
/**
 * ���̎���ł̎��Ԃ��擾����
 */
float GetLapTime(float Time, const TArray<float>& LapTimes) {
	//���܂ł̃Q�[�����Ԃ���O��܂ł̃��b�v�^�C���̍��v�l���������ƂŁA����̃��b�v�^�C�����v�Z����
	return Time - std::accumulate(LapTimes.begin(), LapTimes.end(), 0.0f);
}
}	 // namespace

// Sets default values for this component's properties
ULapCounter::ULapCounter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULapCounter::BeginPlay() {
	Super::BeginPlay();

	MostAdvancedIndex = 0;
	MostAdvancedLapCount = 1;
	CurrentIndex = 0;
	CurrentLapCount = 1;

	AActor* RaceManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ARaceManager::StaticClass());
	RaceManager = Cast<ARaceManager>(RaceManagerActor);
}

// Called every frame
void ULapCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// �`�F�b�N�|�C���g��ʉ߂���
void ULapCounter::PassCheckPoint(ACheckPoint* PassedCheckPoint) {
	const int32 PassedCheckPointIndex = PassedCheckPoint->GetIndex();
	int32 Random = FMath::RandRange(0, 10000);
	constexpr int32 START_CHECKPOINT_INDEX = 0;

	//���񎞂̉����Đ�����
	auto PlayLapIncrementSound = [](int32 NextLapCount) {
		//���b�v����3->4�ɂȂ������̓S�[��SE���Đ�����
		const ESoundResourceType Sound =
			NextLapCount == 4 ? ESoundResourceType::SE_RACE_GOAL : ESoundResourceType::SE_RACE_LAP_COUNT;
		UMyGameInstance::GetInstance()->GetSoundSystem()->PlaySound2D(Sound);
	};

	// �X�^�[�g�n�_�̃`�F�b�N�|�C���g
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// ���܂łɐi�񂾍ő�̃`�F�b�N�|�C���g���R�[�X�̍Ō�̃C���f�b�N�X�Ȃ�1�T���Ă����Ƃ�������
		if (MostAdvancedIndex == MaxCheckPointIndex) {
			MostAdvancedLapCount++;

			//���݂̎��Ԃ��獡��̃��b�v�^�C�����擾���A���b�v�^�C���ɒǉ�����
			float Time = RaceManager->GetRaceTimer()->GetCurrentTime();
			LapTimes.Add(GetLapTime(Time, LapTimes));
			MostAdvancedIndex = PassedCheckPointIndex;

			AActor* ParentActor = GetOwner();

			//�}���`�ڑ����Ȃ玩�����I�[�i�[�̎��ɉ����Đ�����
			if (UNetworkConnectUtility::IsMultiGame(GetWorld())) {
				if (UNetworkConnectUtility::IsOwner(ParentActor)) {
					PlayLapIncrementSound(MostAdvancedLapCount);
				}
			} else {
				//�V���O���v���C�Ȃ玩�����v���C���[�̎��ɍĐ�����
				if (Cast<ABoat>(ParentActor)->GetRacerInfo().PlayerIndex == 0) {
					PlayLapIncrementSound(MostAdvancedLapCount);
				}
			}
			LapIncrementDispatcher.Broadcast(MostAdvancedLapCount);
		}
	} else {
		// ���̃`�F�b�N�|�C���g�ɐG�ꂽ�炻�̏��ōX�V
		if (MostAdvancedIndex + 1 == PassedCheckPointIndex) {
			MostAdvancedIndex = PassedCheckPointIndex;
		}
	}

	// ���ʌ���p�̃C���f�b�N�X�̍X�V����
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// ���񂵂��^�C�~���O�ŉ��Z
		if (CurrentIndex == MaxCheckPointIndex) {
			CurrentLapCount++;
		}
	} else if (PassedCheckPointIndex == MaxCheckPointIndex) {
		// �߂����^�C�~���O�Ō��Z
		if (CurrentIndex == START_CHECKPOINT_INDEX) {
			CurrentLapCount = FMath::Max(CurrentLapCount - 1, 0);
		}
	}
	CurrentIndex = PassedCheckPointIndex;
}

TArray<float> ULapCounter::GetLapTimes() const {
	return LapTimes;
}
