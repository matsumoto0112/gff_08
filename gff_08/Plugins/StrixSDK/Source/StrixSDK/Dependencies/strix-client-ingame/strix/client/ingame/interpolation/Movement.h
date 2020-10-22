#pragma once

#include <strix/client/ingame/interpolation/Common.h>

namespace strix { namespace client { namespace ingame { namespace interpolation {

/**
 *  A pairing of 3d position and velocity
 */
class Movement {
public:
    Movement() {
    }

    Movement(const glm::vec3 &position) {
	 m_position = position;
    }

    Movement(const glm::vec3 &position, const glm::vec3 &velocity) {
	 m_position = position;
	 m_velocity = velocity;
    }

    /**
     *  Get the position of this movement
     *  @returns	The position
     */
    const glm::vec3 &GetPosition() const {
	 return m_position;
    }

    /**
     *	Set the position of this movement
     *	@param	position	The position
     */
    void SetPosition(const glm::vec3 &position) {
	 m_position = position;
    }

    /**
     *	Get the velocity of this movement
     *	@returns	The velocity
     */
    const glm::vec3 &GetVelocity() const {
	 return m_velocity;
    }

    /**
     *	Set the velocity of this movement
     *	@param	velocity	The velocity
     */
    void SetVelocity(const glm::vec3 &velocity) {
	 m_velocity = velocity;
    }

private:
	glm::vec3 m_position;
    glm::vec3 m_velocity;
};

} } } }
