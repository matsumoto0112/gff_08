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

#include <chrono>

namespace movement {

/**
 *  StrixMovementController for local actors.
 *  
 *  Checks the actor for movement changes and notifies the listening component
 *  about them.
 */
class StrixLocalMovementController : public StrixMovementController
{
public:
	StrixLocalMovementController(AActor *pOwner, strix::client::ingame::interpolation::MovementInterpolator interpolator);

	/** Checks whether the synchronization is required and updates
	 *  the information about last position/rotation.
	 *  If sync is required it sets the sync required flag.
	 *  @param	deltaTime	Time since last tick
	 *  @param	shouldSync	Output flag for setting whether the values should be synchronized or not
	 */
	void UpdateMovement(float deltaTime, bool& shouldSync) override;

	/** Not used by the local implementation of the movement controller.
	 */
	void Refresh() override;

private:
	/** Internal function for checking whether the values should be synchronized or not.
	 *  @param	location	New location of the object
	 *  @param	rotation	New rotation of the object
	 *  @param	now	Current time point
	 */
	bool IsSyncRequired(const glm::vec3 &location, FQuat rotation, const std::chrono::steady_clock::time_point &now);

	/** Checks whether the object moved since last tick or not
	 *  @param	position	Current position of the object
	 */
	bool IsMoved(const glm::vec3 &position);

	/** Checks whether the object was rotated since last tick or not
	 *  @param	rotation	Current rotation of the object
	 */
	bool IsRotated(const FQuat &rotation) const;

	/** Updates the values used for replication with the ones from the interpolator
	 *  @param	position	Current position of the object
	 *  @param	velocity	Current velocity of the object
	 *  @param	now	Current time point
	 */
	void UpdateStoredValues(const glm::vec3 &position, const glm::vec3 &velocity, const std::chrono::steady_clock::time_point &now);

	FQuat m_lastRotation;
	strix::client::ingame::interpolation::MovementInterpolator m_movementInterpolator;
	glm::vec3 m_lastPosition;
	std::chrono::steady_clock::time_point m_lastTime;
};

}
