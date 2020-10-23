/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Util/ActorUtil.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Launch/Resources/Version.h"

const FName ActorUtil::DisabledVisibilityActorTag = FName("ActorUtil_DisabledVisibility");
const FName ActorUtil::DisabledTickActorTag = FName("ActorUtil_DisabledTick");
const FName ActorUtil::DisabledCollisionActorTag = FName("ActorUtil_DisabledCollision");
const FName ActorUtil::DisabledSimulatePhysicsActorTag = FName("ActorUtil_DisabledSimulatePhysics");

void ActorUtil::EnableActor(AActor *actor)
{
	if (IsValid(actor))
	{
		if (actor->ActorHasTag(DisabledVisibilityActorTag))
		{
			actor->SetActorHiddenInGame(false);
			actor->Tags.Remove(DisabledVisibilityActorTag);
		}
		if (actor->ActorHasTag(DisabledTickActorTag))
		{
			actor->SetActorTickEnabled(true);
			actor->Tags.Remove(DisabledTickActorTag);
		}
		if (actor->ActorHasTag(DisabledCollisionActorTag))
		{
			actor->SetActorEnableCollision(true);
			actor->Tags.Remove(DisabledCollisionActorTag);
		}
		if (actor->ActorHasTag(DisabledSimulatePhysicsActorTag))
		{
			if (auto primitiveComponent = Cast<UPrimitiveComponent>(actor->GetRootComponent()))
			{
				primitiveComponent->SetSimulatePhysics(true);
			}
			actor->Tags.Remove(DisabledSimulatePhysicsActorTag);
		}
	}
}

void ActorUtil::DisableActor(AActor *actor)
{
	if (IsValid(actor))
	{
#if ENGINE_MINOR_VERSION >= 24
		if (!actor->IsHidden())
#else
		if (!actor->bHidden)
#endif
		{
			actor->SetActorHiddenInGame(true);
			actor->Tags.Add(DisabledVisibilityActorTag);
		}
		if (actor->IsActorTickEnabled())
		{
			actor->SetActorTickEnabled(false);
			actor->Tags.Add(DisabledTickActorTag);
		}
		if (auto primitiveComponent = Cast<UPrimitiveComponent>(actor->GetRootComponent()))
		{
			if (primitiveComponent->GetBodyInstance()->bSimulatePhysics)
			{
				primitiveComponent->SetSimulatePhysics(false);
				actor->Tags.Add(DisabledSimulatePhysicsActorTag);
			}
		}
		if (actor->GetActorEnableCollision())
		{
			actor->SetActorEnableCollision(false);
			actor->Tags.Add(DisabledCollisionActorTag);
		}
	}
}

void ActorUtil::DisablePawnControl(AActor *actor)
{
	if (auto pawn = Cast<APawn>(actor))
	{
		pawn->AutoPossessPlayer = EAutoReceiveInput::Disabled;
		pawn->AutoReceiveInput = EAutoReceiveInput::Disabled;
	}
}

void ActorUtil::SpawnDefaultAIController(AActor* actor)
{
	if (auto pawn = Cast<APawn>(actor))
	{
		if (pawn->GetController())
			pawn->GetController()->Destroy();

		pawn->AutoPossessAI = EAutoPossessAI::Spawned;
		pawn->AIControllerClass = ((APawn*)APawn::StaticClass()->GetDefaultObject())->AIControllerClass;
		pawn->SpawnDefaultController();
	}
}

void ActorUtil::IteratePropertyTree(AActor *rootActor, bool iterateInheritedProps, std::function<void(UObject *, UProperty *)> operation)
{
	if(!rootActor)
	{
		return;
	}
	IterateProperties(rootActor, iterateInheritedProps, operation);
	for (auto component : rootActor->GetComponents())
	{
		if (component)
		{
			if (auto childActor = Cast<UChildActorComponent>(component))
			{
				IteratePropertyTree(childActor->GetChildActor(), iterateInheritedProps, operation);
			}
			else
			{
				IterateProperties(component, iterateInheritedProps, operation);
			}
		}
	}
}

void ActorUtil::IterateProperties(UObject *object, bool iterateInheritedProps, std::function<void(UObject *, UProperty *)> operation)
{
	TFieldIterator<UProperty> it(
		object->GetClass(),
		iterateInheritedProps ? EFieldIteratorFlags::IncludeSuper : EFieldIteratorFlags::ExcludeSuper,
		EFieldIteratorFlags::ExcludeDeprecated
	);
	for (; it; ++it)
	{
		operation(object, *it);
	}
}
