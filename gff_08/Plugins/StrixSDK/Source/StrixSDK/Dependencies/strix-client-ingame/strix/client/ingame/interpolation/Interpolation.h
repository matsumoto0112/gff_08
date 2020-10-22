#pragma once

#include <strix/client/ingame/interpolation/Common.h>
#include <strix/client/ingame/interpolation/Movement.h>

namespace strix { namespace client { namespace ingame { namespace interpolation {

/**
 *  Functions for calculating interpolation with Bezier curves
 */
class Interpolation {
public:

    /**
     *	 Calculate the interpolated between two linear values at a given time
     *	 @param	p0	The old value
     *	 @param	p1	The new value 1 time unit ahead of p0
     *	 @param	t	The time in units to calculate the position for
     *	 @returns	The value at time t
     */
    static float Linear(float p0, float p1, float t) {
        float p = (p1 - p0) * t + p0;
        return p;
    }

    /**
     *  Calculate the linear interpolation between two points in 3d space at a given time
     *  @param	p0	The x, y, z vector of the old position
     *  @param	p1	The x, y, z vector of the new position, 1 time unit ahead of p0
     *  @param	t	The time in units to calculate the position for
     *  @returns	A x, y, z vector representing the position at time t
     */
    static glm::vec3 Linear(const glm::vec3 &p0, const glm::vec3 &p1, float t) {
        glm::vec3 p = (p1 - p0) * t + p0;
        return p;
    }

    /**
     *  Calculate the y value of the Bezier curve between two points at a given point in time
     *  @param	p0	The starting point of the curve
     *  @param	p1	The second control point
     *  @param	p2	The third control point
     *  @param	p3	The destination, 1 time unit ahead of p0
     *  @param	t	The time in units to calculate the position for
     *  @returns	The value of the curve at time t
     */
    static float Bezier(float p0, float p1, float p2, float p3, float t) {
        float u = 1 - t;
        float p = u * u * u * p0
                + 3 * u * u * t * p1
                + 3 * u * t * t * p2
                + t * t * t * p3;

        return p;
    }

    /**
     *  Calculate the position on a 3d Bezier curve between two points at a given point in time
     *  @param	p0	The starting point of the curve, an x, y, z vector
     *  @param	p1	The second control point, an x, y, z vector
     *  @param	p2	The third control point, an x, y, z vector
     *  @param	p3	The destination, 1 time unit ahead of p0, an x, y, z vector
     *  @param	t	The time in units to calculate the position for
     *  @returns	The value of the curve at time t, an x, y, z vector
     */
    static glm::vec3 Bezier(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, float t) {
        glm::vec3 p;

        for (int i = 0; i < 3; i++) {
            p[i] = Bezier(p0[i], p1[i], p2[i], p3[i], t);
        }

        return p;
    }

    /**
     *  Calculate the derivative of the Bezier curve between two points at a given point in time
     *  @param	p0	The starting point of the curve
     *  @param	p1	The second control point
     *  @param	p2	The third control point
     *  @param	p3	The destination, 1 time unit ahead of p0
     *  @param	t	The time in units to calculate the derivative for
     *  @returns	The derivative of the curve at time t
     */
    static float BezierDerivative(float p0, float p1, float p2, float p3, float t) {
        float u = 1 - t;
        float p = 3 * u * u * (p1 - p0)
                + 6 * u * t * (p2 - p1)
                + 3 * t * t * (p3 - p2);

        return p;
    }

    /**
     *  Calculate the derivative of a 3d Bezier curve between two points at a given point in time
     *  @param	p0	The starting point of the curve, an x, y, z vector
     *  @param	p1	The second control point, an x, y, z vector
     *  @param	p2	The third control point, an x, y, z vector
     *  @param	p3	The destination, 1 time unit ahead of p0, an x, y, z vector
     *  @param	t	The time in units to calculate the derivative for
     *  @returns	The derivative of the curve at time t, an x, y, z vector
     */
    static glm::vec3 BezierDerivative(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, float t) {
        glm::vec3 p;

        for (int i = 0; i < 3; i++) {
            p[i] = BezierDerivative(p0[i], p1[i], p2[i], p3[i], t);
        }

        return p;
    }

    /**
     *  Calculate a Movement to match the Bezier curve given source, destination and time
     *  @param	p0	The starting point of the curve, an x, y, z vector
     *  @param	v0	The starting tangent (i.e, velocity), an x, y, z vector
     *  @param	p1	The destination point of the curve after 1 time unit, an x, y, z vector
     *  @param	v1	The final tangent (i.e, velocity), an x, y, z vector
     *  @param	scale	The scaling factor to apply
     *  @param	t	The time in units to calculate the movement for
     *  @return	The movement value (a position and velocity) for the curve at time t
     */
    static Movement BezierFromCoordAndTangent(const glm::vec3 &p0, const glm::vec3 &v0, const glm::vec3 &p1, const glm::vec3 &v1, float scale, float t) {
        glm::vec3 c0 = p0 + v0 * scale;
        glm::vec3 c1 = p1 - v1 * scale;

        glm::vec3 p = Bezier(p0, c0, c1, p1, t);
        glm::vec3 v = BezierDerivative(p0, c0, c1, p1, t);

        return Movement(p, v);
    }
};

} } } }