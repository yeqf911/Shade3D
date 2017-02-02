#ifndef _VEC3_H_
#define _VEC3_H_

#include <iostream>

namespace Shade
{
namespace Maths
{
	struct vec3;
	std::ostream& operator<<(std::ostream& stream, const vec3& vector);

	struct vec3
	{
		float x, y, z;
		vec3();
		vec3(const float& x, const float& y, const float& z);

		vec3& add(const vec3 other);
		vec3& subtract(const vec3 other);
		vec3& multiply(const vec3 other);
		vec3& divide(const vec3 other);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		bool operator==(const vec3& other);
		bool operator!=(const vec3& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	};

} // namespace maths
} // namespace shade

#endif // _VEC3_H_
