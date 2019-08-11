#include "Map.h"
#include <SDL.h>

Map::Map() :
	nWidth(0),
	nHeight(0),
	mSolids(nullptr),
	mIndices(nullptr)
{

}
Map::~Map()
{
	delete[] mIndices;
	//TODO delete[] mSolids;
}

bool Map::CreateDummy(int width, int height, const std::string map)
{
	name = "Asset/map.txt";
	nWidth = width;
	nHeight = height;
	mIndices = new char[width * height];

	memcpy(mIndices, map.c_str(), width * height);
	return true;
}

char Map::GetIndex(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
	{
		return mIndices[y * nWidth + x];
	}
	else
	{
		return 0;
	}
}
char Map::GetSolid(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
	{
		return mSolids[y * nWidth + x];
	}
	else
	{
		return 0;
	}
}

bool Map::LoadMap(const std::string& filepath)
{
	SDL_RWops* file = SDL_RWFromFile(filepath.c_str(), "r+b");
	if (file == nullptr)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, ("[ResourceManager] Unable to open Map %s", filepath.c_str()));
		return false;
	}

	SDL_Log("[ResourceManager] Reading Map...");
	name = filepath;
	SDL_RWread(file, &nWidth, sizeof(char), 1);
	SDL_RWread(file, &nHeight, sizeof(char), 1);
	mIndices = new char[nWidth * nHeight];
	for (int i = 0; i < nWidth * nHeight; i++)
	{
		SDL_RWread(file, &mIndices[i], sizeof(char), 1);
	}

	SDL_RWclose(file);
	return true;
}

bool Map::SaveMap()
{
	SDL_RWops* file = SDL_RWFromFile(name.c_str(), "r+b");
	if (file == nullptr)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, ("[ResourceManager] Unable to find Map %s", name.c_str()));

		file = SDL_RWFromFile(name.c_str(), "w+b");

		if (file == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("[ResourceManager] Unable to Create Map! %s , SDL_ERROR:%s", name.c_str()), SDL_GetError());
			return false;
		}
		SDL_Log("[ResourceManager] New Empty file created");
	}

	SDL_Log("[ResourceManager] Writing to File...");
	SDL_RWwrite(file,&nWidth, sizeof(char), 1);
	SDL_RWwrite(file, &nHeight, sizeof(char), 1);
	for (int i = 0; i < nWidth * nHeight; i++)
	{
		SDL_RWwrite(file, &mIndices[i], sizeof(char), 1);
	}
	SDL_RWclose(file);
}