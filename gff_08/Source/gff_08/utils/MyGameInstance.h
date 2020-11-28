// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "gff_08/network/NetworkData.h"
#include "gff_08/sound/SoundDataAsset.h"
#include "gff_08/sound/SoundSystem.h"
#include "gff_08/utils/GamePlayData.h"
#include "gff_08/utils/OptionParameter.h"
#include "gff_08/utils/PlayUserData.h"

#include "MyGameInstance.generated.h"

/**
 * �Q�[�����ɏ�ɑ��݂���C���X�^���X
 */
UCLASS()
class GFF_08_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

private:
	/**
	 * �R���X�g���N�^
	 */
	UMyGameInstance();

public:
	/**
	 * ������
	 */
	virtual void Init() override;

	/**
	 * �I��������
	 */
	virtual void Shutdown() override;
	/**
	 * ���s����Blueprint�̃R�[���X�^�b�N�����O�o�͂���
	 */
	UFUNCTION(BlueprintCallable, Category = "Debug")
	static void PrintLogBlueprintCallstack();
	/**
	 * �C���X�^���X�̎擾
	 */
	UFUNCTION(BlueprintPure, Category = "MyGameInstance")
	static UMyGameInstance* GetInstance();
	/**
	 * �T�E���h�V�X�e���̎擾
	 */
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	USoundSystem* GetSoundSystem() const;

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	FAllRacersGamePlayData GetPlayData() const {
		return PlayData;
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	void SetPlayData(const FAllRacersGamePlayData& Data) {
		this->PlayData = Data;
		if (this->PlayData.Player1Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player1Data.LapTimes[0], this->PlayData.Player1Data.LapTimes[1],
					this->PlayData.Player1Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player1Data.LapTimes[0], this->PlayData.Player1Data.LapTimes[1],
				this->PlayData.Player1Data.LapTimes[2]);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player1Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player1Data.LapTimes.Num());
		}
		if (this->PlayData.Player2Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player2Data.LapTimes[0], this->PlayData.Player2Data.LapTimes[1],
					this->PlayData.Player2Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player2Data.LapTimes[0], this->PlayData.Player2Data.LapTimes[1],
				this->PlayData.Player2Data.LapTimes[2]);

		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player2Data LapTimes.Num() != 3... Num = "), this->PlayData.Player2Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player2Data.LapTimes.Num());
		}
		if (this->PlayData.Player3Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player3Data.LapTimes[0], this->PlayData.Player3Data.LapTimes[1],
					this->PlayData.Player3Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player3Data.LapTimes[0], this->PlayData.Player3Data.LapTimes[1],
				this->PlayData.Player3Data.LapTimes[2]);

		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player3Data LapTimes.Num() != 3... Num = "), this->PlayData.Player3Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player1Data LapTimes.Num() != 3... Num = "), this->PlayData.Player3Data.LapTimes.Num());
		}
		if (this->PlayData.Player4Data.LapTimes.Num() == 3) {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
					this->PlayData.Player4Data.LapTimes[0], this->PlayData.Player4Data.LapTimes[1],
					this->PlayData.Player4Data.LapTimes[2]));
			UE_LOG(LogTemp, Log, TEXT("Set Play Data Called. PlayerIndex: %d LapTime is %f,%f,%f"), this->PlayData.MyBoatIndex,
				this->PlayData.Player4Data.LapTimes[0], this->PlayData.Player4Data.LapTimes[1],
				this->PlayData.Player4Data.LapTimes[2]);
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
				FString::Printf(TEXT("Player4Data LapTimes.Num() != 3... Num = "), this->PlayData.Player4Data.LapTimes.Num()));
			UE_LOG(LogTemp, Log, TEXT("Player4Data LapTimes.Num() != 3... Num = "), this->PlayData.Player4Data.LapTimes.Num());
		}
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UOptionParameter* GetOption() const {
		return Option;
	}
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UPlayUserData* GetUserData() const {
		return UserData;
	}
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UNetworkData* GetNetworkData() const {
		return NetworkData;
	}

protected:
	//! OnHandleSystemError �f���Q�[�g�o�^���̃n���h��
	FDelegateHandle OnSystemErrorDelegateHandle;
	/**
	 * �V�X�e���G���[���ɌĂ΂��֐�
	 */
	void OnSystemError();

protected:
	//! �T�E���h�f�[�^�̃A�Z�b�g
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundDataAsset* SoundDataAsset;

protected:
	//! �T�E���h�V�X�e��
	UPROPERTY()
	USoundSystem* SoundSystem;
	//! �Q�[���̃v���C���
	UPROPERTY()
	FAllRacersGamePlayData PlayData;
	//! �I�v�V�������
	UPROPERTY()
	UOptionParameter* Option;
	//! ���[�U�[�̏��
	UPROPERTY()
	UPlayUserData* UserData;
	//! �l�b�g���[�N�̏��
	UPROPERTY()
	UNetworkData* NetworkData;
};
