#pragma once
#include "Engine/Math.h"
#include <SDL.h>

class GameObject
{
public:
	GameObject();
	~GameObject();


	Engine::Vec2 pos;
	Engine::Vec2 vel;
	SDL_Rect clip;
	SDL_Rect collider;

	bool CheckCollision(const GameObject& other);
	bool CheckCollision(const GameObject& a, const GameObject& b);

};

