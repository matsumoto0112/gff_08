/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <functional>

class AActor;

/** Class containing various utility functions for managing actors.
 */
class ActorUtil
{

public:
	/** "Enables" the actor, showing it in game and allowing it to tick/process collisions
	 *	@param	actor	Actor to enable
	 */
	static void EnableActor(AActor *actor);

	/** "Disables" the actor, hiding it in game and removing the tick/collision processing
	 *	@param	actor	Actor to disable
	 */
	static void DisableActor(AActor *actor);

	/** Removes the input processing from the actor
	 *	@param	actor	Actor to remove the input processing from
	 */
	static void DisablePawnControl(AActor *actor);

	/** Spawns the default AI controller on the actor, allowing it to process inputs
	 *	@param	actor	Actor to spawn the controller on
	 */
	static void SpawnDefaultAIController(AActor *actor);
private:
	/**
	 *  Helper tag for marking hidden actors
	 */
	static const FName DisabledVisibilityActorTag;

	/**
	 *  Helper tag for marking actors with disabled ticks
	 */
	static const FName DisabledTickActorTag;

	/**
	 *  Helper tag for marking actors with disabled collisions
	 */
	static const FName DisabledCollisionActorTag;

	/**
	 *  Helper tag for marking actors with disabled physics
	 */
	static const FName DisabledSimulatePhysicsActorTag;
public:
	/** Iterates the properties of an actor and performs the specified operation on them
	 *	@param	rootActor	Actor to get the properties from
	 *	@param	iterateInheritedProps	Whether or not to process inherited properties
	 *	@param	operation	The operation to perform on the properties
	 */
	static void IteratePropertyTree(AActor *rootActor, bool iterateInheritedProps, std::function<void(UObject *, UProperty *)> operation);

	/** Iterates the properties of an object and performs the specified operation on them
	 *	@param	object	Object to get the properties from
	 *	@param	iterateInheritedProps	Whether or not to process inherited properties
	 *	@param	operation	The operation to perform on the properties
	 */
	static void IterateProperties(UObject *object, bool iterateInheritedProps, std::function<void(UObject *, UProperty *)> operation);
};
