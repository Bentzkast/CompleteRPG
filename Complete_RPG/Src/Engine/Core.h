#pragma once
#include <SDL.h>
#include <string>

#include "Math.h"
#include "Color.h"

namespace Engine {
	class Game {
	public:
		Game();

	public:
		bool Construct(const char* title, uint32_t width, uint32_t height, bool fullScreen);
		bool Start();

	public: // override Interface
		// called once the game startup, use to load asset
		virtual bool OnGameStart() = 0;
		// called every frame, provide a deltaTime (time per frame
		virtual bool OnUpdate(float deltaTime) = 0;
		// called once before game terminates
		virtual bool OnGameDestroy() = 0;

	public: // utility
	public: // draw routine here
		void Clear(Color color);
	private:
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
		Uint32 m_nTicks;
		bool m_isRunning;

	private:
		//AssetManager* m_pAssetManager;
		//Map* m_pMap;
		//InputSystem* m_pInputSystem;

		// TODO
	private:
		//Vector2f m_cameraPos = { 0,0 };
		//Vector2f m_playerPos = { 0, 0 };
		//Vector2f m_playerVel = { 0, 0 };
		//float m_playerSpeed = 6.0f;

		//float m_playerFrame = 0.0f;

	private:
		std::string m_title;
		uint32_t m_screenWidth;
		uint32_t m_screenHeight;
		bool m_isFullScreen;


	private:
		void processInput();
		void updateGame();
		void renderDisplay();
		void shutdown();
		//void RenderSprite(const Sprite *s, int xPos, int yPos);
	};
}
