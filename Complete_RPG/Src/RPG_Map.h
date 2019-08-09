#pragma once
#include <string>
#include "Engine/Sprite.h"
class RPG_Map
{
public:
	RPG_Map();
	~RPG_Map();

public:
	int Width;
	int Height;
	std::string Name;

public:
	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);
	const Engine::Sprite* pSprite = nullptr;
	bool Create(const std::string& fileData,const Engine::Sprite* sprite, const std::string& name);

private:
	int *m_indices = nullptr;
	bool *m_solids = nullptr;
};

