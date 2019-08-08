#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Constant.h"
#include "AssetManager.h"
#include "InputSystem.h"
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
	InputSystem* m_pInputSystem;

	// TODO
private:
	Vec2 m_cameraPos = { 0,0 };
	Vec2 m_playerPos = { 0, 0 };
	Vec2 m_playerVel = { 0, 0 };
	float m_playerSpeed = 6.0f;

	float m_playerFrame = 0.0f;

private:
	void processInput();
	void updateGame();
	void renderDisplay();

private:
	void RenderSprite(const Sprite *s, int xPos, int yPos);
};