// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
	}

	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UOptionParameter* GetOption() const {
		return Option;
	}
	UFUNCTION(BlueprintCallable, Category = "MyGameInstance")
	UPlayUserData* GetUserData() const {
		return UserData;
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
};
