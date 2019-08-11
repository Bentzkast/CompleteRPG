#include "RPG.h"
#include <iostream>

bool RPG::OnGameStart()
{
	SDL_Log("Game Start");
	LoadSprite("Asset/char64.png", "hero");
	LoadSprite("Asset/tile64.png", "tiles");
	map = new Map();

	std::string tex;

	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "....................................########....................";
	tex += "...........................................#....................";
	tex += "....................................#####..#....................";
	tex += "....................................#...#..#....................";
	tex += ".....................###############....#.#.....................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";
	tex += "................................................................";


	map->CreateDummy(64,16,tex);
	//map->LoadMap("Asset/map.txt");

	for (int y = 0; y < map->nHeight; y++)
	{
		for (int x = 0; x < map->nWidth; x++)
		{
			std::cout << map->GetIndex(x, y);
		}
		std::cout << "\n";
	}

	// TODO FIX WORLD SCALLING ISSUE
	player = new Player();
	player->pos = Engine::Vec2(0, 0) * 64;
	player->vel = Engine::Vec2(10, 0);
	player->collider.x = player->pos.x;
	player->collider.y = player->pos.y;
	// TODO PUSH THESE STUFF TO THE GO
	player->clip = SDL_Rect{ 0, 11 * 64, 64, 64 };

	box.pos = Engine::Vec2(5  , 5) * 64;
	box.collider.x = box.pos.x;
	box.collider.y = box.pos.y;
	// TODO BOX spawner
	box.clip = SDL_Rect{ 5 * 64, 0 * 64, 64, 64 };
	return true;
}

bool RPG::OnUpdate(float deltaTime) 
{
	Clear(Engine::GREY);
	/*if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_L) == Engine::EReleased)
	{
		map->LoadMap("Asset/map.txt");

		for (int y = 0; y < map->nHeight; y++)
		{
			for (int x = 0; x < map->nWidth; x++)
			{
				std::cout << map->GetIndex(x, y);
			}
			std::cout << "\n";
		}
	}*/
	player->vel.x = 0;
	player->vel.y = 0;

	if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_UP) == Engine::EHeld)
	{
		player->vel.y = -6;
	}
	if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == Engine::EHeld)
	{
		player->vel.y = 6;
	}
	if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == Engine::EHeld)
	{
		player->vel.x = -6;
	}
	if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == Engine::EHeld)
	{
		player->vel.x = 6;
	}

	if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_S) == Engine::EReleased)
	{
		map->SaveMap();

		for (int y = 0; y < map->nHeight; y++)
		{
			for (int x = 0; x < map->nWidth; x++)
			{
				std::cout << map->GetIndex(x, y);
			}
			std::cout << "\n";
		}
	}

	/*----------------------------PHYSIC STUFF---------------------*/

	player->pos.x += player->vel.x;
	player->collider.x = player->pos.x;

	if (player->CheckCollision(box))
	{
		SDL_Log("COLIDE!");
		player->pos.x -= player->vel.x;
		player->collider.x -= player->pos.x;
		player->vel.x = 0;
	}

	player->pos.y += player->vel.y;
	player->collider.y = player->pos.y;

	if (player->CheckCollision(box))
	{
		SDL_Log("COLIDE!");
		player->pos.y -= player->vel.y;
		player->collider.y -= player->pos.y;
		player->vel.y = 0;
	}



	/*----------------------------RENDER STUFF---------------------*/
	const Engine::Sprite* heroSprite = GetSprite("hero");
	const Engine::Sprite* tileSprite = GetSprite("tiles");


	for (int y = 0; y < map->nHeight; y++)
	{
		for (int x = 0; x < map->nWidth; x++)
		{
			char tileId = map->GetIndex(x, y);
			switch (tileId)
			{
				case '.':
				{
					SDL_Rect c{ 0, 0 * 64, 64, 64 };
					DrawPartialSprite(
						tileSprite,
						Engine::Vec2{ 
							static_cast<float>(x * 64),
							static_cast<float>(y * 64) },
						&c);
				}
				break;
				case '#':
				{
					SDL_Rect c{ 0, 7 * 64, 64, 64 };
					DrawPartialSprite(
						tileSprite,
						Engine::Vec2{
							static_cast<float>(x * 64),
							static_cast<float>(y * 64) },
							&c);
				}
				break;
				default:
				break;
			}
		}
		
	}
	



	// TODO WORLD SCALE
	Engine::Vec2 playerScreenPos = player->pos;
	Engine::Vec2 boxScreenPos = box.pos;



	DrawPartialSprite(heroSprite, playerScreenPos, &player->clip);
	DrawPartialSprite(tileSprite, boxScreenPos, &box.clip);

	return true;
}
bool RPG::OnGameDestroy()
{
	SDL_Log("Game Destroyed");
	delete map;
	delete player;
	return true;
}