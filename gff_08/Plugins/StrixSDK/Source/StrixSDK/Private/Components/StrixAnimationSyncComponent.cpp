/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Components/StrixAnimationSyncComponent.h"

#include "Animation/AnimInstance.h"
#include "Sync/UESyncProperties.h"
#include "Util/ActorUtil.h"
#include "Engine/BlueprintGeneratedClass.h"

UStrixAnimationSyncComponent::UStrixAnimationSyncComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UStrixAnimationSyncComponent::BeginPlay()
{
	Super::BeginPlay();

	m_replicator = GetOwner()->FindComponentByClass<UStrixReplicatorComponent>();

	if (AActor* actor = Cast<AActor>(GetOwner()))
	{
		m_skeleton = Cast<USkeletalMeshComponent>(actor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		if (m_skeleton == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("StrixAnimationSyncComponent:BeginPlay - Could not find skeletal mesh for actor: %s"), *GetOwner()->GetName());
		}
		else
		{
			SyncProperties();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StrixAnimationSyncComponent:BeginPlay - %s is not an actor"), *GetOwner()->GetName());
	}
}

void UStrixAnimationSyncComponent::SyncProperties()
{
	UAnimInstance* anim = m_skeleton->GetAnimInstance();
	ActorUtil::IterateProperties(anim, false, [&](UObject* object, UProperty* prop)
	{
		if (Cast<UBlueprintGeneratedClass>(object->GetClass()) && prop->HasAnyPropertyFlags(CPF_Net))
		{
			if (prop->HasAnyPropertyFlags(CPF_RepNotify))
			{
				UESyncPropertyUtils::SyncUEProperty(prop, object, m_replicator->GetDefaultSyncGroup(), prop->RepNotifyFunc, GetOwner());
			}
			else
			{
				UESyncPropertyUtils::SyncUEProperty(prop, object, m_replicator->GetDefaultSyncGroup());
			}
		}
	});
}
