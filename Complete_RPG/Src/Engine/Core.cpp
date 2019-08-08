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
		//m_pInputSystem->PrepareForUpdate();

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

	void Game::renderDisplay()
	{
		SDL_RenderPresent(m_pRenderer);
	}

	void Game::shutdown()
	{
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		OnGameDestroy();
	}
}