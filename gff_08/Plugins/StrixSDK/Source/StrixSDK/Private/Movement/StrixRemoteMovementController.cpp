/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#include "Movement/StrixRemoteMovementController.h"


#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Util/ActorUtil.h"
#include "Util/GlmHelper.h"

using namespace strix::client::ingame::interpolation;

namespace movement {

const float StrixRemoteMovementController::MaxFloorDistance = 2.4f;
const FName StrixRemoteMovementController::FloorTraceName = FName(TEXT("RemoteControllerFloorSweep"));

StrixRemoteMovementController::StrixRemoteMovementController(AActor *pOwner, const MovementInterpolator &movementInterpolator)
	: m_movementInterpolator(movementInterpolator)
{
	m_pOwner = pOwner;
	m_lastRotation = pOwner->GetActorRotation().Quaternion();
	m_nextRotation = m_lastRotation;
	m_lastSyncTime = 0;
	m_interpolationPeriod = 1.0f;
	m_syncPeriodMin = 100;
	m_syncPeriodMax = 500;
	m_lastMove = Movement();

	if (const auto pawn = Cast<APawn>(pOwner))
	{
		m_movementComponent = pawn->GetMovementComponent();
	}
	else
	{
		m_movementComponent = nullptr;
	}

	m_movementInterpolator.Reset(util::GlmHelper::Convert(pOwner->GetActorLocation()));

	pOwner->DisableInput(nullptr);
	ActorUtil::SpawnDefaultAIController(pOwner);
}

void StrixRemoteMovementController::UpdateMovement(float deltaTime, bool& shouldSync)
{
	FVector location = m_pOwner->GetActorLocation();

	Movement m(util::GlmHelper::Convert(location), util::GlmHelper::Convert(m_lastVelocity));
	MovementInterpolator::InterpolatedMovement currentInterpolatedMovement = m_movementInterpolator.Move(m, deltaTime);

	FVector currentInterpolatedVelocity = util::GlmHelper::Convert(currentInterpolatedMovement.velocity);

	bool updated = false;

	if (m_movementComponent)
	{
		if (currentInterpolatedMovement.movementType == MovementInterpolator::MovementType::Move)
		{
			UCharacterMovementComponent* characterMovement = dynamic_cast<UCharacterMovementComponent*>(m_movementComponent);
			if (characterMovement)
			{
				if (characterMovement->MovementMode == MOVE_Custom)
				{
					UpdateMovementWithPositionOnly(currentInterpolatedMovement);
					updated = true;
				}
				else if (characterMovement->MovementMode == MOVE_Flying)
				{
					UpdateMovement(currentInterpolatedVelocity, true);
					updated = true;
				}
			}

			if (!updated)
			{
				UpdateMovement(currentInterpolatedVelocity);
				updated = true;
			}
		}
	}

	if (!updated)
	{
		UpdateMovementWithPositionOnly(currentInterpolatedMovement);
	}

	if (m_interpolateRotation)
	{
		double elapsed = (FDateTime::Now() - m_lastSyncTime).GetTotalSeconds();

		float t = static_cast<float>(elapsed / m_interpolationPeriod);

		if (t < 0.0f)
		{
			t = 0.0f;
		}
		else if (t > 2.0f)
		{
			t = 2.0f;
		}

		m_pOwner->SetActorRotation(FQuat::Slerp(m_lastRotation, m_nextRotation, t));
	}
	else
	{
		m_pOwner->SetActorRotation(m_nextRotation);
	}
	m_lastVelocity = currentInterpolatedVelocity;
	shouldSync = false;
}

void StrixRemoteMovementController::Refresh()
{
	Movement current = Movement(
		glm::vec3(m_positionX, m_positionY, m_positionZ),
		glm::vec3(m_velocityX, m_velocityY, m_velocityZ)
	);

	MovementSnapshot movement(current, std::chrono::steady_clock::now());

	m_movementInterpolator.GetMovementPath().Add(movement);

	m_lastMove = current;

	m_lastRotation = m_nextRotation;
	m_nextRotation = FQuat(m_rotationX, m_rotationY, m_rotationZ, m_rotationW);

	FDateTime currentTime = FDateTime::Now();

	if (m_lastRotation != m_nextRotation)
	{

		if (m_lastSyncTime == 0)
		{
			m_lastRotation = m_nextRotation;
			m_interpolationPeriod = 1.0f;
		}
		else
		{
			m_interpolationPeriod = static_cast<float>((currentTime - m_lastSyncTime).GetTotalSeconds());

			if (m_interpolationPeriod < 0.01f)
				m_interpolationPeriod = 0.01f;
		}

		m_lastSyncTime = currentTime;
	}
}

void StrixRemoteMovementController::UpdateMovementWithPositionOnly(const MovementInterpolator::InterpolatedMovement &currentInterpolatedMovement)
{
	FVector pos = util::GlmHelper::Convert(currentInterpolatedMovement.position);
	m_pOwner->SetActorLocation(pos);
}

void StrixRemoteMovementController::UpdateMovement(FVector velocity, bool isFlying)
{
	m_movementComponent->RequestDirectMove(velocity, false);
	if (m_movementComponent->IsFalling())
	{
		if (m_syncX)m_movementComponent->Velocity.X = velocity.X;
		if (m_syncY)m_movementComponent->Velocity.Y = velocity.Y;
		if (m_syncZ)
		{
			if (isFlying
				|| FGenericPlatformMath::Abs<float>(m_movementComponent->GetGravityZ()) < KINDA_SMALL_NUMBER
				|| !IsAdjustingFloorPenetration())
			{
				m_movementComponent->Velocity.Z = velocity.Z;
			}
		}
	}
	m_movementComponent->UpdateComponentVelocity();
}

// ToDo: this seems to work better PostPhysics, consider changing
bool StrixRemoteMovementController::IsAdjustingFloorPenetration()
{
	if (m_positionZ < m_pOwner->GetActorLocation().Z)
	{
		return (m_pOwner->GetActorLocation().Z - m_positionZ) > MaxFloorDistance;
	}

	float boundBoxExtentZ = m_movementComponent->UpdatedComponent->Bounds.BoxExtent.Z;
	float boundBoxEndZ = m_positionZ - boundBoxExtentZ;

	FVector start = FVector(m_positionX, m_positionY, m_positionZ);
	FVector end = start + (FVector(0, 0, -1) * (2 * boundBoxExtentZ));

	FCollisionQueryParams traceParams(FloorTraceName, false, m_movementComponent->GetOwner());
	FHitResult outHit = FHitResult(ForceInit);

	bool isHit = m_movementComponent->GetWorld()->LineTraceSingleByChannel(
		outHit,
		start,
		end,
		m_movementComponent->UpdatedComponent->GetCollisionObjectType(),
		traceParams
	);

	return isHit ? FGenericPlatformMath::Abs<float>(boundBoxEndZ - outHit.ImpactPoint.Z) < MaxFloorDistance : false;
}


}
