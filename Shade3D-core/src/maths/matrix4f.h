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
			vec4 columns[4];	// ���Է������ݵ���֯�����ǿ������ȡ��һ�г���
		};

		matrix4f();
		matrix4f(float diagonal);
		matrix4f(const matrix4f& matrix4);

		matrix4f& multiply(const matrix4f other);
		friend matrix4f operator*(const matrix4f& left, const matrix4f& right);
		matrix4f& operator*=(const matrix4f& other);
	
		/* ��λ���� */
		static matrix4f identity();

		// ͸�Ӿ��� fov = field of view, aspect = ���� */
		static matrix4f perspective(float fov, float aspect, float near, float far);

		/* ���Ӿ��� */
		static matrix4f orthographic(float left, float right, float top, float bottom, float near, float far);

		/* ƽ�ƾ��󣬸þ������ʹָ��ʸ��ƽ�� vector ����λ */
		static matrix4f translation(const vec3& vector);

		/* ��ת���� */
		static matrix4f rotation(float angle, const vec3& axis);// axix :��

		/* ���ž��� */
		static matrix4f scale(const vec3& scale);

		friend std::ostream& operator<<(std::ostream& stream, const matrix4f& mat4);
		 
	};

} // namespace Maths
} // namespace Shade

#endif // _MATRIX4F_H_
