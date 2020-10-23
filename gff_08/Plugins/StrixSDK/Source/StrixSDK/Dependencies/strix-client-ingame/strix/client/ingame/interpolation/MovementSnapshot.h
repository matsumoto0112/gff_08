#pragma once

#include <strix/client/ingame/interpolation/Common.h>
#include <strix/client/ingame/interpolation/Movement.h>

namespace strix { namespace client { namespace ingame { namespace interpolation {

/**
 *  A 3d movement (position and velocity) and a timestamp, representing a position and movement at a given time
 */
class MovementSnapshot
{
public:

    MovementSnapshot() {
    }
	
    MovementSnapshot(const MovementSnapshot &rhs)
	: m_movement(rhs.m_movement),
	 m_timestamp(rhs.m_timestamp)
    {
    }

    MovementSnapshot(const glm::vec3 &position)
	: m_movement(position)
    {
    }

    MovementSnapshot(const Movement &movement, const std::chrono::steady_clock::time_point &timestamp) 
	 : m_movement(movement), m_timestamp(timestamp) 
    {
    }

    /**
    *  Get the movement (position and velocity) of this snapshot
    *  @returns	The movement
    */
    const Movement &GetMovement() const 
    {
	 return m_movement;
    }

    /**
    *  Set the movement (position and velocity) of this snapshot
    *  @param	movement	The movement
    */
    void SetMovement(const Movement &movement)
    {
	 m_movement = movement;
    }

    /**
     *	 Get the timestamp of this snapshot
     *	 @returns	The timestamp
     */
    const std::chrono::steady_clock::time_point &GetTimestamp() const 
    {
	 return m_timestamp;
    }

    /**
     *	 Set the timestamp of this snapshot
     *	 @param	timestamp	The timestamp
     */
    void SetTimestamp(const std::chrono::steady_clock::time_point &timestamp) 
    {
	 m_timestamp = timestamp;
    }

private:
	Movement m_movement;
    std::chrono::steady_clock::time_point m_timestamp;
};

} } } }