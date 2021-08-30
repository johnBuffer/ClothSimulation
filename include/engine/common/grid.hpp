#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>


template<typename T>
struct Grid
{
	struct HitPoint
	{
		T* cell;
		float dist;

		HitPoint()
			: cell(nullptr)
			, dist(0.0f)
		{}
	};

	int32_t width, height;
	std::vector<T> data;

	Grid()
		: width(0)
		, height(0)
	{
	}

	Grid(int32_t width_, int32_t height_)
		: width(width_)
		, height(height_)
	{
		data.resize(width * height);
	}

	int32_t mod(int32_t dividend, int32_t divisor) const
	{
		return (dividend%divisor + divisor) % divisor;
	}

	template<typename Vec2Type>
	bool checkCoords(const Vec2Type& v) const
	{
		return checkCoords(v.x, v.y);
	}

	bool checkCoords(int32_t x, int32_t y) const
	{
		return x > 0 && x < (width - 1) && y > 0 && y < (height - 1);
	}

	const T& get(int32_t x, int32_t y) const
	{
		return data[y * width + x];
	}

	template<typename Vec2Type>
	T& get(const Vec2Type& v)
	{
		return get(v.x, v.y);
	}

	template<typename Vec2Type>
	const T& get(const Vec2Type& v) const
	{
		return get(v.x, v.y);
	}

	template<typename Vec2Type>
	const T& getWrap(Vec2Type v) const
	{
		return getWrap(v.x, v.y);
	}

	const T& getWrap(int32_t x, int32_t y) const
	{
		return get(mod(x, width), mod(y, height));
	}

	T& get(int32_t x, int32_t y)
	{
		return data[y * width + x];
	}

	template<typename Vec2Type>
	void set(const Vec2Type& v, const T& obj)
	{
		set(v.x, v.y, obj);
	}

	void set(int32_t x, int32_t y, const T& obj)
	{
		data[y * width + x] = obj;
	}

	template<typename Vec2Type>
	HitPoint getFirstHit(Vec2Type p, Vec2Type d, float max_dist)
	{
		HitPoint intersection;
		sf::Vector2i cell_p(p.x, p.y);
		const sf::Vector2i step(d.x < 0.0f ? -1 : 1, d.y < 0.0f ? -1 : 1);
		const sf::Vector2f inv_d(1.0f / d.x, 1.0f / d.y);
		const float t_dx = std::abs(inv_d.x);
		const float t_dy = std::abs(inv_d.y);
		float t_max_x = ((cell_p.x + (step.x > 0)) - p.x) * inv_d.x;
		float t_max_y = ((cell_p.y + (step.y > 0)) - p.y) * inv_d.y;
		while (intersection.dist < max_dist) {
			const uint32_t b = t_max_x < t_max_y;
			// Advance in grid
			intersection.dist = b * t_max_x + (!b) * t_max_y;
			t_max_x += t_dx * b;
			t_max_y += t_dy * (!b);
			cell_p.x += step.x * b;
			cell_p.y += step.y * (!b);
			if (!checkCoords(cell_p)) {
				return intersection;
			}
			else {
				T& cell = get(cell_p);
				if (cell.atoms_count) {
					intersection.cell = &cell;
					//intersection.normal = sf::Vector2f(to<float>(b), to<float>(!b));
					return intersection;
				}
			}
		}
		return intersection;
	}
};
