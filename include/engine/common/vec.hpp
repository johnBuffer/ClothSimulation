#pragma once
#include <cmath>


struct Vec2
{
	Vec2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vec2(float x_, float y_)
		: x(x_)
		, y(y_)
	{}

	float getLength2() const
	{
		return x * x + y * y;
	}

	float getLength() const
	{
		return sqrt(getLength2());
	}

	Vec2 operator/(float f) const
	{
		const float inv = 1.0f / f;
		return Vec2(x * inv, y * inv);
	}

	Vec2 operator*(float f) const
	{
		return Vec2(x * f, y * f);
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator-() const
	{
		return Vec2(-x, -y);
	}

	void operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator+=(float f)
	{
		x += f;
		y += f;
	}

	void operator/=(float f)
	{
		x /= f;
		y /= f;
	}

	Vec2 plus(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 minus(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	void operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void rotate(const Vec2& origin, float angle)
	{
		const Vec2 v = *this - origin;

		// This should be precomputed
		const float ca = cos(angle);
		const float sa = sin(angle);

		const float new_x = v.x * ca - v.y * sa;
		const float new_y = v.x * sa + v.y * ca;

		x = new_x + origin.x;
		y = new_y + origin.y;
	}

	Vec2 getNormal() const
	{
		return Vec2(-y, x);
	}

	float dot(const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}

	float cross(const Vec2& other) const
	{
		return x * other.y - y * other.x;
	}

	Vec2 getNormalized() const
	{
		return (*this) / getLength();
	}

	static Vec2 rotate(Vec2 v, const Vec2& origin, float angle)
	{
		v.rotate(origin, angle);
		return v;
	}

	float x, y;
};


struct IVec2
{
	int32_t x, y;

	IVec2()
		: x(0)
		, y(0)
	{}

	IVec2(int32_t x_, int32_t y_)
		: x(x_)
		, y(y_)
	{}
};
