#include "matrix4f.h"
#include "maths.h"

namespace Shade
{
namespace Maths
{
	matrix4f operator*(const matrix4f& left, const matrix4f& right);
	std::ostream& operator<<(std::ostream& stream, const matrix4f& mat4);

	matrix4f::matrix4f()
	{
		for (int i = 0; i < 4*4; ++i)
		{
			_element[i] = 0.0f;
		}
	}

	matrix4f::matrix4f(float diagonal)
	{
		for (int i = 0; i < 4*4; ++i)
		{
			_element[i] = 0.0f;
		}
		_element[0 + 0 * 4] = diagonal;
		_element[1 + 1 * 4] = diagonal;
		_element[2 + 2 * 4] = diagonal;
		_element[3 + 3 * 4] = diagonal;
	}

	matrix4f::matrix4f(const matrix4f& matrix4)
	{
		for (int i =0; i < 4*4; ++i)
		{
			_element[i] = matrix4._element[i];
		}
	}


	matrix4f matrix4f::identity()
	{
		return matrix4f(1.0f);
	}

	matrix4f& matrix4f::multiply(const matrix4f other)
	{
		float tmpElement[16] = { 0.0f };
		for (int i = 0; i < 4*4; ++i)	/* 先拷贝一份原来的，因为循环的时候不能改变原矩阵的元素 */
		{
			tmpElement[i] = _element[i];
		}
		for (int raw = 0; raw < 4; ++raw)
		{
			for (int col = 0; col < 4; ++col)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; ++e)
				{
					sum += tmpElement[raw + e * 4] * other._element[col * 4 + e];
				}
				_element[raw + col * 4] = sum;
			}
		}
		return *this;
	}

	matrix4f operator*(const matrix4f& left, const matrix4f& right)
	{
		matrix4f result(left);
		return result.multiply(right);
	}

	matrix4f& matrix4f::operator*=(const matrix4f& other)
	{
		return multiply(other);
	}

	matrix4f matrix4f::perspective(float fov, float aspect, float far, float near)
	{
		matrix4f mat4;
		float radianFov = degree2radian(fov);
		float tanHalfFov = static_cast<float>(tan(radianFov / 2));

		mat4._element[0 + 0 * 4] = 1.0f / (aspect * tanHalfFov);
		mat4._element[1 + 1 * 4] = 1.0f / tanHalfFov;
		mat4._element[2 + 2 * 4] = -(far + near) / (far - near);
		mat4._element[2 + 3 * 4] = -(2.0f * far * near) / (far - near);
		mat4._element[3 + 2 * 4] = -1.0f;
		return mat4;
	}

	matrix4f matrix4f::orthographic(float left, float right, float top, float bottom, float far, float near)
	{
		matrix4f mat4 = matrix4f(1.0f);
		mat4._element[0 + 0 * 4] = 2.0f / (right - left);
		mat4._element[1 + 1 * 4] = 2.0f / (top - bottom);
		mat4._element[2 + 2 * 4] = -2.0f / (far - near);
		mat4._element[0 + 3 * 4] = -(right + left) / (right - left);
		mat4._element[1 + 3 * 4] = -(top + bottom) / (top - bottom);
		mat4._element[2 + 3 * 4] = -(far + near) / (far - near);
		return mat4;
	}

	matrix4f matrix4f::translation(const vec3& translate)
	{
		matrix4f mat4(1.0f);
		mat4._element[0 + 3 * 4] = translate.x;
		mat4._element[1 + 3 * 4] = translate.y;
		mat4._element[2 + 3 * 4] = translate.z;
		return mat4;
	}

	matrix4f matrix4f::rotation(float angle, const vec3& axis)
	{
		matrix4f mat4(1.0f);
		// TODO: rotation
		return mat4;
	}

	matrix4f matrix4f::scale(const vec3& scale)
	{
		matrix4f mat4(1.0f);
		mat4._element[0 + 0 * 4] = scale.x;
		mat4._element[1 + 1 * 4] = scale.y;
		mat4._element[2 + 2 * 4] = scale.z;
		return mat4;
	}

	std::ostream& operator<<(std::ostream& stream, const matrix4f& mat4)
	{
		char buffer[40] = { 0 };
		for (int raw = 0; raw < 4; ++raw)
		{
			float a, b, c, d;
			a = mat4._element[raw + 4 * 0];
			b = mat4._element[raw + 4 * 1];
			c = mat4._element[raw + 4 * 2];
			d = mat4._element[raw + 4 * 3];
			sprintf_s(buffer, sizeof(buffer), "[%7.2f %7.2f %7.2f %7.2f]\n", a, b, c, d);
			stream << buffer;
		}	
		return stream;
	}

} // namespace Maths
} // namespace Shade 