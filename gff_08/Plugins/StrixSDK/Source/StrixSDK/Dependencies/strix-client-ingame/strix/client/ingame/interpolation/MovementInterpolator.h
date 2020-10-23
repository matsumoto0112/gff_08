#pragma once

#include <strix/client/ingame/interpolation/Common.h>
#include <strix/client/ingame/interpolation/Movement.h>
#include <strix/client/ingame/interpolation/MovementPath.h>

namespace strix { namespace client { namespace ingame { namespace interpolation {

/**
 *  Performs movement interpolation
 */
class MovementInterpolator
{
public:

	/**
	 *  Types of movement
	 */
	enum class MovementType
	{
		Idle,
		Move,
		Teleport
	};

	/**
	 *  A pair consisting of a movement in 3d space and a movement type
	 */
	struct InterpolatedMovement
	{
		glm::vec3 position;
		glm::vec3 velocity;
		MovementType movementType;
	};

	/**
	 *  Construct a movement interpolator with a starting position
	 *  @param	position	The starting position
	 */
	MovementInterpolator(const glm::vec3 &position);

	/**
	 *  Construct a movement interpolator with settings from another movement interpolator and a starting position
	 *  @param	rhs	The interpolator to copy from
	 *  @param	position	The starting position
	 */
	MovementInterpolator(const MovementInterpolator &rhs, const glm::vec3 &position);

	/**
	 *  Get the near distance
	 *  @returns	The near distance
	 */
	float GetNearDistance() const {
		return m_nearDistance;
	}

	/**
	 *  Set the near distance
	 *  @param	nearDistance	The near distance
	 */
	void SetNearDistance(float nearDistance) {
		m_nearDistance = nearDistance;
	}

	/**
	 *  Get the max speed
	 *  @returns	The max speed
	 */
	float GetMaxSpeed() const {
		return m_maxSpeed;
	}

	/**
	 *  Set the max speed
	 *  @param	maxSpeed	The max speed
	 */
	void SetMaxSpeed(float maxSpeed) {
		m_maxSpeed = maxSpeed;
	}

	/**
	 *  Get the acceleration
	 *  @returns	The acceleration
	 */
	float GetAcceleration() const {
		return m_acceleration;
	}

	/**
	 *  Set the acceleration
	 *  @param	acceleration	The acceleration
	 */
	void SetAcceleration(float acceleration) {
		m_acceleration = acceleration;
	}

	/**
	 *  Get the damping
	 *  @returns	The damping
	 */
	float GetDamping() const {
		return m_damping;
	}

	/**
	 *  Set the damping
	 *  @param	damping	The damping
	 */
	void SetDamping(float damping) {
		m_damping = damping;
	}

	/**
	 *  Get the timestep
	 *  @returns	The timestep
	 */
	float GetTimestep() const {
		return m_timestep;
	}

	/**
	 *  Set the timestep
	 *  @param	timestep	The timestep
	 */
	void SetTimestep(float timestep) {
		m_timestep = timestep;
	}

	/**
	 *  Get the prediction period
	 *  @returns	The prediction period
	 */
	int GetPredictionPeriod() const {
		return m_predictionPeriod;
	}

	/**
	 *  Set the prediction period
	 *  @param	predictionPeriod	The prediction period
	 */
	void SetPredictionPeriod(int predictionPeriod) {
		m_predictionPeriod = predictionPeriod;
	}

	/**
	 *  Get the reachable distance
	 *  @returns	The reachable distance
	 */
	float GetReachableDistance() const
	{
		return m_reachableDistance;
	}

	/**
	 *  Set the reachable distance
	 *  @param	distance	The reachable distance
	 */
	void SetReachableDistance(float distance)
	{
		m_reachableDistance = distance;
	}

	/**
	 *  Get the movement path
	 *  @returns	The movement path
	 */
	MovementPath &GetMovementPath() {
		return m_movementPath;
	}

	/**
	 *  Resets the movement path with the given snapshot
	 *  @param	movementSnapshot	The snapshot to add to the path
	 */
	void Reset(MovementSnapshot movementSnapshot);

	/**
	 *  Get the interpolated movement between the current movement and previous over delta time
	 *  @param	currentMovement	The current movement
	 *  @param	dt	The delta value between 0 and 1
	 *  @returns	The interpolated movement
	 */
	InterpolatedMovement Move(const Movement &currentMovement, float dt);

	/**
	 *  Predicts the movement at the given time. If the time is further in the future than the movement path,
	 *  then this will extrapolate the movement for that time. Otherwise it will interpolate the value.
	 *  @param	time	The time to predict for
	 *  @returns	The predicted movement
	 */
	MovementSnapshot Predict(const std::chrono::steady_clock::time_point &time);

private:
	void UpdatePath(const Movement &movement, const std::chrono::steady_clock::time_point &now);

	InterpolatedMovement Step(const Movement &movement, const MovementSnapshot &desiredMovement, float speed, float dt);

	float ChangeSpeed(const Movement &movement, const MovementSnapshot &desiredMovement, float dt);

	MovementSnapshot Interpolate(const MovementSnapshot *currentPathPoint, const MovementSnapshot *lastPathPoint, const std::chrono::steady_clock::time_point &time);

	MovementSnapshot Extrapolate(const MovementSnapshot *currentPathPoint, const MovementSnapshot *lastPathPoint, const std::chrono::steady_clock::time_point &time);

	bool ReachedGoal(const glm::vec3 &position, const Movement &goal);

	bool ReachedGoal(const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &destination);

	bool IsTimeout(const std::chrono::steady_clock::time_point &time, const std::chrono::steady_clock::time_point &now);

	bool IsAccelerating(float s0, float s1, float t) const;

	glm::vec3 Simulate(const glm::vec3 &p1, const glm::vec3 &dir, float speed, float acceleration, float damping, float maxSpeed, float t, float timeStep) const;

	float AdjustSpeed(float speed, float dt, float maxDistance);

	MovementPath m_movementPath;
	float m_nearDistance;
	float m_maxSpeed;
	float m_acceleration;
	float m_damping;
	float m_timestep;
	int m_predictionPeriod;
	float m_reachableDistance;
};

} } } }