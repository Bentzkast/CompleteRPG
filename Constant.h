#pragma once
#include <SDL.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const SDL_Color BLACK = SDL_Color{ 10, 10, 10, 255 };
// Resolution of the sprite sheet
const int PIXEL_RESOLUTION = 16;
// Pixel scale in game screen
const int PIXEL_SCALE = 4;

struct Vector2f {
	float x;
	float y;

	Vector2f operator+ (Vector2f const&obj) {
		Vector2f res;
		res.x += obj.x;
		res.y += obj.y;

		return res;
	}
};
