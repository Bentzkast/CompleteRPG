#include "Engine.h"

Engine::Engine() :
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_nTicks(0),
	m_isRunning(true)
{}

bool Engine::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init SDL Video %s", SDL_GetError());
		return false;
	}
	SDL_Log("SDL Video initialization Successfull");


	m_pWindow = SDL_CreateWindow("Simple Tower Defense",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0); // Flags for Open GL latter

	if (m_pWindow == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init SDL Window %s", SDL_GetError());
		return false;
	}
	SDL_Log("Window initialization Successfull");

	m_pRenderer = SDL_CreateRenderer(
		m_pWindow,
		-1, // Defailt
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

	SDL_Log("Initialization Successfull");
	return true;
}

void Engine::Run() {
	while (m_isRunning) {
		processInput();
		updateGame();
		renderDisplay();
	}
}
void Engine::Close() {


	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_isRunning = false;
				break;
			default:
				break;
			}
		}

		default:
			break;
		}
	}

}

void Engine::updateGame() {
	// Frame limiting to prevent jumpy movemen
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_nTicks + 16));

	float deltaTime = (SDL_GetTicks() - m_nTicks) / 1000.f;

	// Limit deltaTime
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	m_nTicks = SDL_GetTicks();

	// ----------------
}

void Engine::renderDisplay() {
	SDL_Color bgCol = BLACK;
	SDL_SetRenderDrawColor(m_pRenderer, bgCol.r, bgCol.g, bgCol.b, bgCol.a);
	SDL_RenderClear(m_pRenderer);


	// CAMERA CALCULATION - TODO MOVE OUT OF HERE

	m_cameraPos = m_playerPos;

	int nTileWidth = PIXEL_RESOLUTION * PIXEL_SCALE;
	int nTileHeight = PIXEL_RESOLUTION * PIXEL_SCALE;

	// visible time count
	int nVisibleTilesX = SCREEN_WIDTH / nTileWidth;
	int nVisibleTilesY = SCREEN_HEIGHT / nTileHeight;

	// Camera in the middle of the screen
	float fOffsetX = m_cameraPos.x - (float) nVisibleTilesX / 2.0f;
	float fOffsetY = m_cameraPos.y - (float) nVisibleTilesY / 2.0f;

	// Clamp the camera to a sane position
	if (fOffsetX < 0) fOffsetX = 0;
	if (fOffsetY < 0) fOffsetY = 0;
	if (fOffsetX > m_pMap->nLevelWidth - nVisibleTilesX) fOffsetX = m_pMap->nLevelWidth- nVisibleTilesX;
	if (fOffsetY > m_pMap->nLevelHeight - nVisibleTilesY) fOffsetX = m_pMap->nLevelHeight - nVisibleTilesY;


	const Sprite* s = m_pAssetManager->GetSprite("atlas");
	// the display size
	SDL_Rect r{ 0, 0, s->GetWidth(), s->GetHeight() };
	// the clip pos in the sprite sheet.
	SDL_Rect clip_solid{ 17 * PIXEL_RESOLUTION,  17 * PIXEL_RESOLUTION, PIXEL_RESOLUTION, PIXEL_RESOLUTION };

	for (int x = 0; x < nVisibleTilesX; x++){
		for (int y = 0; y < nVisibleTilesY; y++){
			wchar_t sTileID = m_pMap->GetTile(x, y);
			switch (sTileID)
			{
			case L'.':
				break;
			case L'#':
				r = { x *nTileWidth , y * nTileHeight, s->GetWidth(), s->GetHeight() };
				SDL_RenderCopy(m_pRenderer, s->GetTexture(), &clip_solid, &r);
				break;
			default:
				break;
			}
		}
	}

	SDL_RenderPresent(m_pRenderer);
}

void Engine::LoadData() {
	m_pAssetManager = new AssetManager(m_pRenderer);
	m_pAssetManager->LoadSpriteSheet("Asset/atlas.png", "atlas");
	//m_pAssetManager->LoadSpriteSheet("Asset/toml_village.spr", "vill");
	m_pMap = new Map();
}


void Engine::UnloadData() {
	delete m_pAssetManager;
	delete m_pMap;
}