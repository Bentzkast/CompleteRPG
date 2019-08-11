#pragma once
#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "InputSystem.h"
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
		const InputState& GetInputState() const;

	public:
		bool LoadSprite(const std::string& filepath, const std::string& name);
		const Sprite* GetSprite(const std::string& name) const;
		bool LoadBinary(const std::string& filepath, int* buffer, int size, int offset = 0);
		bool SaveBinary(const std::string& filepath, int* buffer, int size, int offset = 0);

	public: // draw routine here
		void Clear(Color color);
		// TODO
		void DrawSprite(const Sprite* sprite, const Vec2& pos);
		// TODO
		void DrawPartialSprite(const Sprite* sprite, const Vec2& pos, const SDL_Rect* clip);
	private:
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
		Uint32 m_nTicks;
		bool m_isRunning;

	private:
		ResourceManager* m_pResourceManager;
		InputSystem* m_pInputSystem;

		// TODO
	private:
		//Map* m_pMap;
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
