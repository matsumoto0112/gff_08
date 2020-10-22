#pragma once

#include <strix/client/ingame/interpolation/Common.h>

namespace strix { namespace client { namespace ingame { namespace interpolation {

/**
 *  Utility functions for vector operations
 */
class VectorUtil {
public:
    static const float EPSILON;

    /**
     *  Safely normalize a vector. If the vector is very small, it will be set to 0, 1, 0
     *  @param	v	A reference to the vector to normalize
     *  @returns	The length of the old vector
     */
    static float NormalizeSafe(glm::vec3 &v) {
        return NormalizeSafe(v, EPSILON);
    }

    /**
     *	 Safely normalize a vector. If the vector length is smaller than the cutoff, it will be set to 0, 1, 0
     *	 @param	v	A reference to the vector to normalize
     *	 @param	epsilon	The cutoff point
     *  @returns	The length of the old vector
     */
    static float NormalizeSafe(glm::vec3 &v, float epsilon) {
        float vLen = glm::length(v);

        if(vLen > epsilon) {
            v /= vLen;
        } else {
            v = glm::vec3(0, 1, 0);
        }

        return vLen;
    }
};

const float VectorUtil::EPSILON = 0.0001f;

} } } }