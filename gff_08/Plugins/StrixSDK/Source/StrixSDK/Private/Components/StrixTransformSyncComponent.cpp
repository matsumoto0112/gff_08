/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Components/StrixTransformSyncComponent.h"

#include "UELogHandler.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Sync/UESyncProperties.h"

#include <functional>


UStrixTransformSyncComponent::UStrixTransformSyncComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStrixTransformSyncComponent::BeginPlay()
{
	Super::BeginPlay();

	m_replicator = GetOwner()->FindComponentByClass<UStrixReplicatorComponent>();
	if(!m_replicator)
	{
		UE_LOG(LogStrix, Log, TEXT("UStrixTransformComponent:BeginPlay - Replicator component is null"));
		return;
	}

	const auto name = std::string(TCHAR_TO_UTF8(*this->GetName()));
	
	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorLocation().X; },
		[&](float x)
		{
			FVector vec = GetOwner()->GetActorLocation();
			vec.X = x;
			GetOwner()->SetActorLocation(vec);
		}, name + m_translationPropertyString + "X"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorLocation().Y; },
		[&](float y)
		{
			FVector vec = GetOwner()->GetActorLocation();
			vec.Y = y;
			GetOwner()->SetActorLocation(vec);
		}, name + m_translationPropertyString + "Y"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorLocation().Z; },
		[&](float z)
		{
			FVector vec = GetOwner()->GetActorLocation();
			vec.Z = z;
			GetOwner()->SetActorLocation(vec);
		}, name + m_translationPropertyString + "Z"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorScale3D().X; },
		[&](float x)
		{
			FVector vec = GetOwner()->GetActorScale3D();
			vec.X = x;
			GetOwner()->SetActorScale3D(vec);
		}, name + m_scalePropertyString + "X"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorScale3D().Y; },
		[&](float y)
		{
			FVector vec = GetOwner()->GetActorScale3D();
			vec.Y = y;
			GetOwner()->SetActorScale3D(vec);
		}, name + m_scalePropertyString + "Y"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorScale3D().Z; },
		[&](float z)
		{
			FVector vec = GetOwner()->GetActorScale3D();
			vec.Z = z;
			GetOwner()->SetActorScale3D(vec);
		}, name + m_scalePropertyString + "Z"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorRotation().Yaw; },
		[&](float x)
		{
			FRotator rot = GetOwner()->GetActorRotation();;
			rot.Yaw = x;
			GetOwner()->SetActorRotation(rot);
		}, name + m_rotationPropertyString + "X"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorRotation().Pitch; },
		[&](float y)
		{
			FRotator rot = GetOwner()->GetActorRotation();;
			rot.Pitch = y;
			GetOwner()->SetActorRotation(rot);
		}, name + m_rotationPropertyString + "Y"));

	m_replicator->AddSyncProperty(std::make_shared<UEFunctionalSyncProperty<float>>(
		[&]() {return GetOwner()->GetActorRotation().Roll; },
		[&](float z)
		{
			FRotator rot = GetOwner()->GetActorRotation();;
			rot.Roll = z;
			GetOwner()->SetActorRotation(rot);
		}, name + m_rotationPropertyString + "Z"));
}
