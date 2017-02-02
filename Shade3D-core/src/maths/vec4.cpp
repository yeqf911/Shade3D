#include "vec4.h"

namespace Shade
{
namespace Maths
{
	vec4::vec4() : x(0), y(0), z(0), w(0) {}

	vec4::vec4(const float& x, const float& y, const float& z, const float& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4& vec4::add(const vec4 other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vec4& vec4::subtract(const vec4 other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vec4& vec4::multiply(const vec4 other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	vec4& vec4::divide(const vec4 other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	vec4& vec4::operator+=(const vec4& other)
	{
		return this->add(other);
	}

	vec4& vec4::operator-=(const vec4& other)
	{
		return this->subtract(other);
	}

	vec4& vec4::operator*=(const vec4& other)
	{
		return this->multiply(other);
	}

	vec4& vec4::operator/=(const vec4& other)
	{
		return this->divide(other);
	}

	bool vec4::operator==(const vec4& other)
	{
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	bool vec4::operator!=(const vec4& other)
	{
		return !(*this == other);
	}

	vec4 operator+(vec4 left, const vec4& right)
	{
		return left.add(right);
	}

	vec4 operator-(vec4 left, const vec4& right)
	{
		return left.subtract(right);
	}

	vec4 operator*(vec4 left, const vec4& right)
	{
		return left.multiply(right);
	}

	vec4 operator/(vec4 left, const vec4& right)
	{
		return left.divide(right);
	}

	bool operator==(const vec4& left, const vec4& right)
	{
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
	}

	bool operator!=(const vec4& left, const vec4& right)
	{
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector)
	{
		stream << "Vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}

} // namespace maths
} // namespace shade

