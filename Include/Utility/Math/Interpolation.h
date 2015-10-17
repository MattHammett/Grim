#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "../Type.h"

namespace Grim
{
	static float32 linearInterpolate(float32 x, float32 y, float32 delta)
	{
		return static_cast<float32>(((1.0f - delta) * x) + (delta * y));
	}
}

#endif