#ifndef _MATHS_H_
#define _MATHS_H_

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "matrix4f.h"

namespace Shade
{
namespace Maths
{
	inline float degree2radian(const float degree)
	{
		float radian = static_cast<float>(degree * (M_PI / 180.0));
		return radian;
	}
} // namespace Maths
} // namespace Shade

#endif //_MATHS_H_