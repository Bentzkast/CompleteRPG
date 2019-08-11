#pragma once
#include "Engine/Core.h"
#include "Engine/Map.h"
#include "Player.h"
#include "Box.h"
#include <string>
class RPG : public Engine::Game
{
public:
	RPG()
	{}

public:
	bool OnGameStart() override;


	bool OnUpdate(float deltaTime) override;

	bool OnGameDestroy() override;

private:
	Map* map;
	Player* player;
	Box box;
};