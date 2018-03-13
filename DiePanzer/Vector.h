#pragma once
#include <sstream>
#include <Windows.h>


class Vector2
{
public:
	Vector2(void)
	{
		Invalidate();
	}
	void Invalidate()
	{
		x = y = std::numeric_limits<float>::infinity();
	}

	Vector2(float X, float Y)
	{
		x = X;
		y = Y;
	}

	Vector2(const float* clr)
	{
		x = clr[0];
		y = clr[1];
	}

	void Init(float ix = 0.0f, float iy = 0.0f)
	{
		x = ix; y = iy;
	}
	bool IsValid() const
	{
		return std::isfinite(x) && std::isfinite(y);
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}
	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	void Zero()
	{
		x = y = 0.0f;
	}

	bool operator==(const Vector2& src) const
	{
		return (src.x == x) && (src.y == y);
	}
	bool operator!=(const Vector2& src) const
	{
		return (src.x != x) || (src.y != y);
	}

	Vector2& operator+=(const Vector2& v)
	{
		x += v.x; y += v.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}
	Vector2& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		return *this;
	}
	Vector2& operator*=(const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}
	Vector2& operator/=(const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}
	Vector2& operator+=(float fl)
	{
		x += fl;
		y += fl;
		return *this;
	}
	Vector2& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		return *this;
	}
	Vector2& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		return *this;
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}
	Vector2 Normalized() const
	{
		Vector2 res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = 0.0f;
		}
		return res;
	}

	float DistTo(const Vector2 &vOther) const
	{
		Vector2 delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.Length();
	}
	float DistToSqr(const Vector2 &vOther) const
	{
		Vector2 delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.LengthSqr();
	}
	float Dot(const Vector2& vOther) const
	{
		return (x*vOther.x + y*vOther.y);
	}

	float LengthSqr(void) const
	{
		return (x*x + y*y);
	}
	float Length() const
	{
		return sqrt(x*x + y*y);
	}

	Vector2& operator=(const Vector2 &vOther)
	{
		x = vOther.x; y = vOther.y;
		return *this;
	}

	Vector2 Vector2::operator-(void) const
	{
		return Vector2(-x, -y);
	}
	Vector2 Vector2::operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 Vector2::operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 Vector2::operator*(float fl) const
	{
		return Vector2(x * fl, y * fl);
	}
	Vector2 Vector2::operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}
	Vector2 Vector2::operator/(float fl) const
	{
		return Vector2(x / fl, y / fl);
	}
	Vector2 Vector2::operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	float x, y;
};

class Vector
{
public:
	Vector(void)
	{
		Invalidate();
	}
	Vector(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
	Vector(const float* clr)
	{
		x = clr[0];
		y = clr[1];
		z = clr[2];
	}

	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		x = ix; y = iy; z = iz;
	}
	bool IsValid() const
	{
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
	}
	void Invalidate()
	{
		x = y = z = std::numeric_limits<float>::infinity();
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}
	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	void Zero()
	{
		x = y = z = 0.0f;
	}

	bool operator==(const Vector& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z);
	}
	bool operator!=(const Vector& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z);
	}

	Vector& operator+=(const Vector& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	Vector& operator-=(const Vector& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	Vector& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		return *this;
	}
	Vector& operator*=(const Vector& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vector& operator/=(const Vector& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	Vector& operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		return *this;
	}
	Vector& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}
	Vector& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		return *this;
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}
	Vector Normalized() const
	{
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float DistTo(const Vector &vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}
	float DistToSqr(const Vector &vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}
	float Dot(const Vector& vOther) const
	{
		return (x*vOther.x + y*vOther.y + z*vOther.z);
	}
	float Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}
	float LengthSqr(void) const
	{
		return (x*x + y*y + z*z);
	}
	float Length2D() const
	{
		return sqrt(x*x + y*y);
	}

	Vector& operator=(const Vector &vOther)
	{
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}

	Vector Vector::operator-(void) const
	{
		return Vector(-x, -y, -z);
	}
	Vector Vector::operator+(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}
	Vector Vector::operator-(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}
	Vector Vector::operator*(float fl) const
	{
		return Vector(x * fl, y * fl, z * fl);
	}
	Vector Vector::operator*(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z);
	}
	Vector Vector::operator/(float fl) const
	{
		return Vector(x / fl, y / fl, z / fl);
	}
	Vector Vector::operator/(const Vector& v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	float x, y, z;
};

inline void CrossProduct(const Vector& a, const Vector& b, Vector& result)
{
	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;
}

inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	Vector result;
	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;
	return result;
}

class Vector4
{
public:
	float values[4];

	Vector4()
	{
		values[0] = values[1] = values[2] = values[3] = 0;
	}

	Vector4(float x, float y, float z, float w)
	{
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = w;
	}

	// Provide array-like index operators for the components of the vector.
	const float& operator[] (int index) const
	{
		return values[index];
	}
	float& operator[] (int index)
	{
		return values[index];
	}
	float Dot(const Vector4& vOther) const
	{
		return (values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3]);
	}
};

