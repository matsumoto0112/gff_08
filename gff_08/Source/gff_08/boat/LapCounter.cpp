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
	constexpr int32 START_CHECKPOINT_INDEX = 0;

	//���񎞂̉����Đ�����
	auto PlayLapIncrementSound = [&](int32 NextLapCount) {
		USoundSystem* SoundSystem = UMyGameInstance::GetInstance()->GetSoundSystem();
		switch (NextLapCount) {
			case 2:	   // 1�T�ڏI�� 2�T�ڊJ�n��
				SoundSystem->PlaySound2D(ESoundResourceType::SE_RACE_LAP_COUNT);
				break;
			case 3:	   // 2�T�ڏI�� 3�T�ڊJ�n��
				SoundSystem->PlaySound2D(ESoundResourceType::SE_RACE_LAP_COUNT);
				SoundSystem->ChangeBGMPitchPattern(BGMPitchPattern::Fast);
				break;
			case 4:	   // 3�T�ڏI�� �S�[����
			{
				SoundSystem->PlaySound2D(ESoundResourceType::SE_RACE_GOAL);
				SoundSystem->PlayBGM(ESoundResourceType::BGM_GOAL);
				RaceManager->GetHUD()->RankingUpdateStop();
				AActor* ParentActor = GetOwner();
				ABoat* ParentBoat = Cast<ABoat>(ParentActor);
				ParentBoat->EnableAutoMode();
			} break;
			default:
				break;
		}
	};

	// �X�^�[�g�n�_�̃`�F�b�N�|�C���g
	if (PassedCheckPointIndex == START_CHECKPOINT_INDEX) {
		// ���܂łɐi�񂾍ő�̃`�F�b�N�|�C���g���R�[�X�̍Ō�̃C���f�b�N�X�Ȃ�1�T���Ă����Ƃ�������
		if (PassedCheckPoint->IsLastCheckPointIndex(MostAdvancedIndex)) {
			MostAdvancedLapCount++;

			//���݂̎��Ԃ��獡��̃��b�v�^�C�����擾���A���b�v�^�C���ɒǉ�����
			const float Time = RaceManager->GetRaceTimer()->GetCurrentTime();
			LapTimes.Add(GetLapTime(Time, LapTimes));
			MostAdvancedIndex = PassedCheckPointIndex;

			AActor* ParentActor = GetOwner();
			ABoat* ParentBoat = Cast<ABoat>(ParentActor);

			//�}���`�ڑ����Ȃ玩�����I�[�i�[�̎��ɉ����Đ�����
			if (UNetworkConnectUtility::IsOwnerPlayerIndex(ParentBoat->GetRacerInfo().PlayerIndex)) {
				PlayLapIncrementSound(MostAdvancedLapCount);
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
		//���O�܂łɂ����C���f�b�N�X�����̃X�e�[�W���Ō�̃`�F�b�N�|�C���g�̃C���f�b�N�X�Ȃ���񂵂Ă����Ƃ�������
		if (PassedCheckPoint->IsLastCheckPointIndex(CurrentIndex)) {
			CurrentLapCount++;
		}
		// �߂����^�C�~���O�Ō��Z
		if (CurrentIndex == START_CHECKPOINT_INDEX + 1) {
			CurrentLapCount = FMath::Max(CurrentLapCount - 1, 0);
		}
	}
	CurrentIndex = PassedCheckPointIndex;
}

TArray<float> ULapCounter::GetLapTimes() const {
	return LapTimes;
}
