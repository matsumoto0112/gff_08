/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Movement/StrixLocalMovementController.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Util/GlmHelper.h"

using namespace strix::client::ingame::interpolation;

namespace movement {

StrixLocalMovementController::StrixLocalMovementController(AActor *pOwner, MovementInterpolator interpolator)
	: m_lastRotation(FQuat()),
	m_movementInterpolator(interpolator),
	m_lastPosition(util::GlmHelper::Convert(pOwner->GetActorLocation())),
	m_lastTime(std::chrono::steady_clock::duration::zero())
{
	m_pOwner = pOwner;
	m_syncPeriodMin = 100;
	m_syncPeriodMax = 500;

	m_positionX = pOwner->GetActorLocation().X;
	m_positionY = pOwner->GetActorLocation().Y;
	m_positionZ = pOwner->GetActorLocation().Z;

	FQuat quarternion = m_pOwner->GetActorRotation().Quaternion();

	m_rotationX = quarternion.X;
	m_rotationY = quarternion.Y;
	m_rotationZ = quarternion.Z;
	m_rotationW = quarternion.W;

	m_velocityX = pOwner->GetVelocity().X;
	m_velocityY = pOwner->GetVelocity().Y;
	m_velocityZ = pOwner->GetVelocity().Z;
}

void StrixLocalMovementController::UpdateMovement(float deltaTime, bool& shouldSync)
{
	glm::vec3 position = util::GlmHelper::Convert(m_pOwner->GetActorLocation());
	FQuat rotation = m_pOwner->GetActorRotation().Quaternion();
	auto now = std::chrono::steady_clock::now();

	if (IsSyncRequired(position, rotation, now))
	{
		glm::vec3 velocity = (position - m_lastPosition) / deltaTime;
		UpdateStoredValues(position, velocity, now);

		shouldSync = true;
	}
	else
	{
		shouldSync = false;
	}

	m_lastPosition = position;
}

void StrixLocalMovementController::Refresh()
{
}

bool StrixLocalMovementController::IsSyncRequired(const glm::vec3 &position, FQuat rotation, const std::chrono::steady_clock::time_point &now)
{
	if (now < m_lastTime + std::chrono::milliseconds(m_syncPeriodMin))
		return false;

	if (now >= m_lastTime + std::chrono::milliseconds(m_syncPeriodMax))
		return IsMoved(position) || IsRotated(rotation);

	MovementSnapshot movement = m_movementInterpolator.Predict(now);

	const glm::vec3 &p1 = movement.GetMovement().GetPosition();
	const float d = glm::distance(p1, position);

	const float rd = rotation.AngularDistance(m_lastRotation);

	return d > m_movementInterpolator.GetNearDistance() || rd > 0.02f;
}

bool StrixLocalMovementController::IsMoved(const glm::vec3 &position)
{
	const MovementSnapshot *m = m_movementInterpolator.GetMovementPath().Get(0);

	if (!m)
		return false;

	return (m->GetMovement().GetVelocity() != glm::vec3(0.0f) || m->GetMovement().GetPosition() != position);
}

bool StrixLocalMovementController::IsRotated(const FQuat& rotation) const
{
	return rotation.AngularDistance(m_lastRotation) > KINDA_SMALL_NUMBER;
}

void StrixLocalMovementController::UpdateStoredValues(const glm::vec3 &position, const glm::vec3 &velocity, const std::chrono::steady_clock::time_point &now)
{
	m_positionX = position.x;
	m_positionY = position.y;
	m_positionZ = position.z;

	m_velocityX = m_syncX ? velocity.x : 0.0f;
	m_velocityY = m_syncY ? velocity.y : 0.0f;
	m_velocityZ = m_syncZ ? velocity.z : 0.0f;

	FQuat desiredRotationQuaternion = m_pOwner->GetActorRotation().Quaternion();

	m_rotationX = desiredRotationQuaternion.X;
	m_rotationY = desiredRotationQuaternion.Y;
	m_rotationZ = desiredRotationQuaternion.Z;
	m_rotationW = desiredRotationQuaternion.W;

	MovementSnapshot movement(
		Movement(position, velocity),
		now
	);
	
	m_movementInterpolator.GetMovementPath().Add(movement);
	m_lastRotation = desiredRotationQuaternion;
	m_lastTime = now;
}

}
