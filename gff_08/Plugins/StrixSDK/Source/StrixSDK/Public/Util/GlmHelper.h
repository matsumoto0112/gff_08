/*
 * Copyright 2019 Soft Gear Co., Ltd. All Rights Reserved.
 *
 * See https://strixengine.com/en/terms-of-use/ for full license details.
 */
#pragma once

#include "CoreMinimal.h"

#include <glm/glm.hpp>

namespace util {

/** Helper class for conversions between UE and OpenGL Mathematics types.
 */
class GlmHelper
{
public:
	/** Convert the UE FVector to glm type
	 *  @param	v	The vector to convert
	 *  @return The converted vector
	 */
	static glm::vec3 Convert(const FVector &v) {
		return glm::vec3(v.X, v.Y, v.Z);
	}

	/** Convert the glm vector to UE FVector
	 *  @param	v	The vector to convert
	 *  @return The converted vector
	 */
	static FVector Convert(const glm::vec3 &v) {
		return FVector(v.x, v.y, v.z);
	}
};

}
