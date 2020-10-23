/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Movement/StrixMovementController.h"

#include <strix/client/ingame/interpolation/MovementInterpolator.h>

class UPawnMovementComponent;

namespace movement {

/**
 *  StrixMovementController for remote actors.
 *  
 *  Computes movement interpolation from synced spatial and velocity information 
 *  and moves pOwner accordingly. Supports walking and flying movement modes, and
 *  falls back to simpler movement under other/custom modes.
 *  
 *  Note: Designed to provide smooth movement for pawns,
 *  however will fallback to setting position directly for non-pawn actors or actors without
 *  movement components.
 */
class StrixRemoteMovementController : public StrixMovementController
{
public:
	StrixRemoteMovementController(AActor *pOwner, const strix::client::ingame::interpolation::MovementInterpolator &movementInterpolator);

	/**
	 *  Called to move the owner
	 *  @param	deltaTime	The time since last update. Used to determine the scale of the movement
	 *  @param	shouldSync	Whether or not the processed data should by synchronized
	 */
	void UpdateMovement(float deltaTime, bool& shouldSync) override;

	/**
	 *  Updates movement information and movement interpolator
	 */
	void Refresh() override;

private:

	/**
	 *  Internal function for updating movement
	 *  @param	velocity	Velocity of the requested movement
	 *  @param	isFlying	Whether the owner is flying (movement mode) or not
	 */
	void UpdateMovement(FVector velocity, bool isFlying = false);

	/**
	 *  Internal function for updating movement with only position. Not as smooth as velocity update
	 *  @param	currentInterpolatedMovement	Current movement information received from the interpolator
	 */
	void UpdateMovementWithPositionOnly(const strix::client::ingame::interpolation::MovementInterpolator::InterpolatedMovement &currentInterpolatedMovement);

	/**
	 *  Internal function for calculating floor penetration on Z axis. Uses MaxFloorDistance
	 */
	bool IsAdjustingFloorPenetration();

	strix::client::ingame::interpolation::MovementInterpolator m_movementInterpolator;
	FVector m_lastVelocity;
	FQuat m_lastRotation;
	FQuat m_nextRotation;
	float m_interpolationPeriod;
	FDateTime m_lastSyncTime;
	strix::client::ingame::interpolation::Movement m_lastMove;
	UPawnMovementComponent *m_movementComponent;

	/**
	 *  The max distance allowable from the floor before we count as touching the floor
	 *  Note: this is closely related to UCharacterMovementComponent::MAX_FLOOR_DIST
	 */
	static const float MaxFloorDistance;

	/**
	 *  The tag used by hit sweeps (for profiling etc.)
	 */
	static const FName FloorTraceName;

};

}
