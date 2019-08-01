#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Constant.h"
#include "AssetManager.h"
#include "Map.h"

class Engine {
public:
	Engine();
	
public:
	bool Init();
	void LoadData();
	void Run();
	void UnloadData();
	void Close();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	Uint32 m_nTicks;
	bool m_isRunning;

private:
	AssetManager* m_pAssetManager;
	Map* m_pMap;

	// TODO
private:
	Vector2f m_cameraPos = { 0,0 };
	Vector2f m_playerPos = { 0, 0 };

private:
	void processInput();
	void updateGame();
	void renderDisplay();
};