#pragma once

namespace Engine {
	struct Vec2 {
		float x;
		float y;

		Vec2(float x, float y) : x(x), y(y) {}

		friend Vec2 operator+(const Vec2& a, const Vec2& b)
		{
			return Vec2(a.x + b.x, a.y + b.y);
		}

		// Vector subtraction (a - b)
		friend Vec2 operator-(const Vec2& a, const Vec2& b)
		{
			return Vec2(a.x - b.x, a.y - b.y);
		}

		// Component-wise multiplication
		// (a.x * b.x, ...)
		friend Vec2 operator*(const Vec2& a, const Vec2& b)
		{
			return Vec2(a.x * b.x, a.y * b.y);
		}

		friend Vec2 operator*(const Vec2 &obj, float scalar)
		{
			return Vec2(scalar * obj.x, scalar * obj.y);
		}



		void operator*=(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;;
		}

		void operator+= (Vec2 const&obj) {
			this->x += obj.x;
			this->y += obj.y;
		}
	};
}

