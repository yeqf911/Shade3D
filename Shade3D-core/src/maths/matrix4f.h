#ifndef _MATRIX4F_H_
#define _MATRIX4F_H_

#define _USE_MATH_DEFINES
#include "vec3.h"
#include "vec4.h"
#include <math.h>

namespace Shade
{
namespace Maths
{

	struct matrix4f
	{
		union
		{
			float _element[16];
			vec4 columns[4];	// 可以方便数据的组织，我们可以随便取出一列出来
		};

		matrix4f();
		matrix4f(float diagonal);
		matrix4f(const matrix4f& matrix4);

		matrix4f& multiply(const matrix4f other);
		friend matrix4f operator*(const matrix4f& left, const matrix4f& right);
		matrix4f& operator*=(const matrix4f& other);
	
		/* 单位矩阵 */
		static matrix4f identity();

		// 透视矩阵 fov = field of view, aspect = 方向 */
		static matrix4f perspective(float fov, float aspect, float near, float far);

		/* 正视矩阵 */
		static matrix4f orthographic(float left, float right, float top, float bottom, float near, float far);

		/* 平移矩阵，该矩阵可以使指定矢量平移 vector 个单位 */
		static matrix4f translation(const vec3& vector);

		/* 旋转矩阵 */
		static matrix4f rotation(float angle, const vec3& axis);// axix :轴

		/* 缩放矩阵 */
		static matrix4f scale(const vec3& scale);

		friend std::ostream& operator<<(std::ostream& stream, const matrix4f& mat4);
		 
	};

} // namespace Maths
} // namespace Shade

#endif // _MATRIX4F_H_
