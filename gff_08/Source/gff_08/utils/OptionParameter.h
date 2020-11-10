// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/NoExportTypes.h"

#include "OptionParameter.generated.h"

/**
 * ���[�U�[�ύX�\�ȃp�����[�^�Ǘ�
 */
UCLASS()
class GFF_08_API UOptionParameter : public USaveGame {
	GENERATED_BODY()

public:
	UOptionParameter();
	~UOptionParameter();

	/**
	 * �f�t�H���g�̒l���Z�b�g����
	 */
	UFUNCTION(BlueprintCallable, Category = "OptionParameter")
	void SetDefaults();

	/**
	 * �}�X�^�[�{�����[���̒l��ݒ肷��
	 */
	UFUNCTION(BlueprintSetter)
	void SetMasterVolume(float Value) {
		MasterVolume = Value;
	}
	/**
	 * �}�X�^�[�{�����[���̒l���擾����
	 */
	UFUNCTION(BlueprintGetter)
	float GetMasterVolume() const {
		return MasterVolume;
	}
	/**
	 * BGM�{�����[���̒l��ݒ肷��
	 */
	UFUNCTION(BlueprintSetter)
	void SetBGMVolume(float Value) {
		BGMVolume = Value;
	}
	/**
	 * BGM�{�����[���̒l���擾����
	 */
	UFUNCTION(BlueprintGetter)
	float GetBGMVolume() const {
		return BGMVolume;
	}
	/**
	 * SE�{�����[���̒l��ݒ肷��
	 */
	UFUNCTION(BlueprintSetter)
	void SetSEVolume(float Value) {
		SEVolume = Value;
	}
	/**
	 * SE�{�����[���̒l���擾����
	 */
	UFUNCTION(BlueprintGetter)
	float GetSEVolume() const {
		return SEVolume;
	}
	/**
	 * ���]���͂��L�����ǂ����̒l��ݒ肷��
	 */
	UFUNCTION(BlueprintSetter)
	void SetFlipInput(bool Value) {
		bFlipInput = Value;
	}
	/**
	 * ���]���͂��L�����ǂ����̒l���擾����
	 */
	UFUNCTION(BlueprintGetter)
	bool GetFlipInput() const {
		return bFlipInput;
	}
	/**
	 * �I�v�V�����f�[�^��ۑ�����
	 */
	UFUNCTION(BlueprintCallable, Category = "Option")
	void SaveOptionData();
	/**
	 * �I�v�V�����f�[�^��ǂݍ���
	 */
	UFUNCTION(BlueprintCallable, Category = "Option")
	void LoadOptionData();

private:
	static const FString SaveSlotName;
	static const uint32 UserIndex;

	//! �}�X�^�[�{�����[��
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetMasterVolume, BlueprintGetter = GetMasterVolume, Category = "OptionParameter")
	float MasterVolume;
	//! BGM�{�����[��
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetBGMVolume, BlueprintGetter = GetBGMVolume, Category = "OptionParameter")
	float BGMVolume;
	//! SE�{�����[��
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetSEVolume, BlueprintGetter = GetSEVolume, Category = "OptionParameter")
	float SEVolume;
	//! ���]���͂�L���ɂ��邩
	UPROPERTY(VisibleAnywhere, BlueprintSetter = SetFlipInput, BlueprintGetter = GetFlipInput, Category = "OptionParameter")
	bool bFlipInput;
};
