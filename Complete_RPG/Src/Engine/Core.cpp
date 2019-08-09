#include "Core.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Engine {

	Game::Game() :
		m_pWindow(nullptr),
		m_pRenderer(nullptr),
		m_nTicks(0),
		m_isRunning(true),
		m_screenWidth(0),
		m_screenHeight(0),
		m_isFullScreen(false),
		m_pInputSystem(nullptr),
		m_title("Game")
	{}

	bool Game::Construct(const char* title, uint32_t width, uint32_t height, bool fullScreen)
	{
		m_screenWidth = width;
		m_screenHeight = height;
		m_isFullScreen = fullScreen;
		m_title = title;

		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init SDL Video %s", SDL_GetError());
			return false;
		}
		SDL_Log("SDL Video initialization Successfull");


		m_pWindow = SDL_CreateWindow("Simple RPG",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_screenWidth,
			m_screenHeight,
			0); // Flags for Open GL latter

		if (m_pWindow == NULL) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init SDL Window %s", SDL_GetError());
			return false;
		}
		SDL_Log("Window initialization Successfull");

		m_pRenderer = SDL_CreateRenderer(
			m_pWindow,
			-1, // default
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		// Init Image loading
		int imgFlags = IMG_INIT_PNG;
		if ((IMG_Init(imgFlags) & imgFlags) == false)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("SDL image could not be initialize! SDL_image ERROR: %s\n", IMG_GetError()));
			return false;
		}
		SDL_Log("SDL Image initialization Successfull");

		if (TTF_Init() == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("SDL ttf could not be initialize! SDL_ttf ERROR: %s\n", TTF_GetError()));
			return false;
		}
		SDL_Log("SDL ttf Initialization Successfull");

		SDL_SetWindowTitle(m_pWindow, m_title.c_str());

		m_pInputSystem = new InputSystem();
		m_pResourceManager = new ResourceManager(m_pRenderer);

		SDL_Log("Initialization Successfull");

		return true;
	}

	bool Game::Start()
	{

		if (!OnGameStart())
		{
			SDL_Log("On Game Start return false!");
		}
		// start the game
		while (m_isRunning) 
		{
			processInput();
			updateGame();
			renderDisplay();
		}
		shutdown();
		return true;
	}


	void Game::processInput()
	{
		m_pInputSystem->PrepareForUpdate();

		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			// could be passed to input system later
			switch (evt.type)
			{
			case SDL_QUIT:
				m_isRunning = false;
				break;
			default:
				break;
			}
		}
	}

	const InputState& Game::GetInputState() const
	{
		return m_pInputSystem->GetState();
	}

	bool Game::LoadSprite(const std::string& filepath, const std::string& name)
	{
		return m_pResourceManager->LoadSprite(filepath, name);
	}

	const Sprite* Game::GetSprite(const std::string& name) const
	{
		return m_pResourceManager->GetSprite(name);
	}

	bool Game::LoadBinary(const std::string& filepath, char* buffer, int size)
	{
		return m_pResourceManager->LoadBinary(filepath, buffer, size);
	}
	bool Game::SaveBinary(const std::string& filepath, char* buffer, int size)
	{
		return m_pResourceManager->SaveBinary(filepath, buffer, size);
	}




	void Game::updateGame()
	{
		// Frame limiting to prevent jumpy movemen
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_nTicks + 16));

		float deltaTime = (SDL_GetTicks() - m_nTicks) / 1000.f;

		// Limit deltaTime
		if (deltaTime > 0.05f) {
			deltaTime = 0.05f;
		}

		m_nTicks = SDL_GetTicks();
		OnUpdate(deltaTime);
	}

	void Game::Clear(Color color)
	{
		SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
		SDL_RenderClear(m_pRenderer);
	}

	// TODO
	void Game::DrawSprite(const Sprite* sprite, const Vec2& pos)
	{
		SDL_Rect r{ pos.x, pos.y,sprite->Width, sprite->Height };
		SDL_RenderCopy(
			m_pRenderer,
			sprite->m_pTexture,
			nullptr,
			&r
		);
	}
	// TODO
	void Game::DrawPartialSprite(const Sprite* sprite, const Vec2& pos, const SDL_Rect* clip)
	{
		SDL_Rect r{ pos.x, pos.y, clip->w, clip->h };
		SDL_RenderCopy(
			m_pRenderer,
			sprite->m_pTexture,
			clip,
			&r
		);
	}

	void Game::renderDisplay()
	{
		SDL_RenderPresent(m_pRenderer);
	}

	void Game::shutdown()
	{
		delete m_pResourceManager;
		delete m_pInputSystem;
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		OnGameDestroy();
	}
}