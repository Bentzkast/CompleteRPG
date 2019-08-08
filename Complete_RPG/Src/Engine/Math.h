#pragma once

namespace Engine {
	struct Vec2 {
		float x;
		float y;

		Vec2(float x, float y) : x(x), y(y) {}

		Vec2 operator+(Vec2 const&obj) {
			return Vec2(x + obj.x, y + obj.y);
		}

		Vec2 operator-(Vec2 const&obj) {
			return Vec2(x - obj.x, y - obj.y);
		}


		void operator+= (Vec2 const&obj) {
			this->x += obj.x;
			this->y += obj.y;
		}
	};
}

