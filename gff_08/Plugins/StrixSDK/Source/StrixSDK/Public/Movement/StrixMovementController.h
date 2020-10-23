/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

namespace movement {

/**
 *  Base class for the StrixMovementController.
 *  
 *  Serves mostly as a storage for common properties.
 */
class StrixMovementController
{
public:
	StrixMovementController() {}
	virtual ~StrixMovementController() {}

	virtual void UpdateMovement(float deltaTime, bool& shouldSync) = 0;

	/** Setter of the SyncX property
	 *	@param	syncX	The value to set
	 */
	void SetSyncX(bool syncX)
	{
		m_syncX = syncX;
	}

	/** Setter of the SyncY property
	 *	@param	syncY	The value to set
	 */
	void SetSyncY(bool syncY)
	{
		m_syncY = syncY;
	}

	/** Setter of the SyncZ property
	 *	@param	syncZ	The value to set
	 */
	void SetSyncZ(bool syncZ)
	{
		m_syncZ = syncZ;
	}

	/** Setter of the SyncJump property
	 *	@param	syncJump	The value to set
	 */
	void SetSyncJump(bool syncJump)
	{
		m_syncJump = syncJump;
	}

	/** Setter of the InterpolateRotation property
	 *	@param	interpolateRotation	The value to set
	 */
	void SetInterpolateRotation(bool interpolateRotation)
	{
		m_interpolateRotation = interpolateRotation;
	}

	/** Getter of the SyncPeriodMin property
	 *  @returns	The value of the property
	 */
	int GetSyncPeriodMin() const {
		return m_syncPeriodMin;
	}

	/** Setter of the SyncPeriodMin property
	 *	@param	syncPeriodMin	The value to set
	 */
	void SetSyncPeriodMin(int syncPeriodMin) {
		m_syncPeriodMin = syncPeriodMin;
	}

	/** Getter of the SyncPeriodMax property
	 *  @returns	The value of the property
	 */
	int GetSyncPeriodMax() const {
		return m_syncPeriodMax;
	}

	/** Setter of the SyncPeriodMax property
	 *	@param	syncPeriodMax	The value to set
	 */
	void SetSyncPeriodMax(int syncPeriodMax) {
		m_syncPeriodMax = syncPeriodMax;
	}

	/** Gets the stored position as FVector
	 *  @returns	Stored position as FVector
	 */
	FVector GetPositionAsVector() const
	{
		return FVector(m_positionX, m_positionY, m_positionZ);
	}

	/** Gets the stored velocity as FVector
	 *  @returns	Stored velocity as FVector
	 */
	FVector GetVelocityAsVector() const
	{
		return FVector(m_velocityX, m_velocityY, m_velocityZ);
	}

	/** Gets the stored rotation as FQuat
	 *  @returns	Stored rotation as FQuat
	 */
	FQuat GetRotationAsQuat() const
	{
		return FQuat(m_rotationX, m_rotationY, m_rotationZ, m_rotationW);
	}

	/** Update the stored values with new ones
	 *  @param	position	New position
	 *  @param	velocity	New velocity
	 *  @param	rotation	New rotation
	 */
	void UpdateStoredValues(const FVector& position, const FVector& velocity, const FQuat& rotation)
	{
		m_positionX = position.X;
		m_positionY = position.Y;
		m_positionZ = position.Z;

		m_velocityX = velocity.X;
		m_velocityY = velocity.Y;
		m_velocityZ = velocity.Z;

		m_rotationX = rotation.X;
		m_rotationY = rotation.Y;
		m_rotationZ = rotation.Z;
		m_rotationW = rotation.W;
	}

	/** Pure virtual function used for refreshing the controller.
	 */
	virtual void Refresh() = 0;

	/** Gets the address of the X value of the stored position
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetPositionXRef()
	{
		return m_positionX;
	}

	/** Gets the address of the Y value of the stored position
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetPositionYRef()
	{
		return m_positionY;
	}

	/** Gets the address of the Z value of the stored position
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetPositionZRef()
	{
		return m_positionZ;
	}

	/** Gets the address of the X value of the stored velocity
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetVelocityXRef()
	{
		return m_velocityX;
	}

	/** Gets the address of the Y value of the stored velocity
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetVelocityYRef()
	{
		return m_velocityY;
	}

	/** Gets the address of the Z value of the stored velocity
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetVelocityZRef()
	{
		return m_velocityZ;
	}

	/** Gets the address of the X value of the stored rotation
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetRotationXRef()
	{
		return m_rotationX;
	}

	/** Gets the address of the Y value of the stored rotation
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetRotationYRef()
	{
		return m_rotationY;
	}

	/** Gets the address of the Z value of the stored rotation
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetRotationZRef()
	{
		return m_rotationZ;
	}

	/** Gets the address of the W value of the stored rotation
	 *  @returns	The address of the requested property
	 *  @remark	This is mostly used by synchronization properties
	 */
	float& GetRotationWRef()
	{
		return m_rotationW;
	}

protected:
	float m_positionX = 0;
	float m_positionY = 0;
	float m_positionZ = 0;

	float m_rotationX = 0;
	float m_rotationY = 0;
	float m_rotationZ = 0;
	float m_rotationW = 0;

	float m_velocityX = 0;
	float m_velocityY = 0;
	float m_velocityZ = 0;

	int m_syncPeriodMin;
	int m_syncPeriodMax;

	bool m_syncX = true;
	bool m_syncY = true;
	bool m_syncZ = true;
	bool m_syncJump = true;
	bool m_interpolateRotation = true;

	AActor *m_pOwner;

};

}