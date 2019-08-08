#pragma once
#include <SDL.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const SDL_Color BLACK = SDL_Color{ 10, 10, 10, 255 };
// Resolution of the sprite sheet
const int PIXEL_RESOLUTION = 64;
// Pixel scale in game screen
const int PIXEL_SCALE = 1;

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
