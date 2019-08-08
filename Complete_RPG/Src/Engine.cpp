#include "Engine.h"

Engine::Engine() :
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_nTicks(0),
	m_isRunning(true),
	m_pAssetManager(nullptr),
	m_pMap(nullptr),
	m_pInputSystem(nullptr)
{}

bool Engine::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init SDL Video %s", SDL_GetError());
		return false;
	}
	SDL_Log("SDL Video initialization Successfull");


	m_pWindow = SDL_CreateWindow("Simple RPG",
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

	SDL_SetWindowTitle(m_pWindow, "Simple RPG");

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
	m_pInputSystem->PrepareForUpdate();

	SDL_Event evt;
	while (SDL_PollEvent(&evt)) {
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
	const InputState&state = m_pInputSystem->GetState();
	m_playerVel = Vec2{ 0,0 };

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_UP) == EHeld) {
		m_playerVel.y = -m_playerSpeed;
	}
	 if (state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == EHeld) {
		 m_playerVel.y = m_playerSpeed;
	}
	 if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EHeld) {
		 m_playerVel.x = -m_playerSpeed;
	}
	 if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EHeld) {
		 m_playerVel.x = m_playerSpeed;
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

	Vec2 newPlayerPos = { 
		m_playerPos.x + m_playerVel.x * deltaTime,
		m_playerPos.y + m_playerVel.y * deltaTime };

	// --- simple collision for player only

	if (m_playerVel.x <= 0) {
		// top left & botom left
		if (m_pMap->GetTileSymbol(newPlayerPos.x + 0.0f, m_playerPos.y + 0.0f) != L'.'
			|| m_pMap->GetTileSymbol(newPlayerPos.x + 0.0f, m_playerPos.y + 0.9f) != L'.') {
			newPlayerPos.x = (int)newPlayerPos.x + 1;
			m_playerVel.x = 0;
		}
	}
	else {
		// top right && bottom right
		if (m_pMap->GetTileSymbol(newPlayerPos.x + 1.0f, m_playerPos.y + 0.0f) != L'.'
			|| m_pMap->GetTileSymbol(newPlayerPos.x + 1.0f, m_playerPos.y +0.9f) != L'.') {
			newPlayerPos.x = (int)newPlayerPos.x;
			m_playerVel.x = 0;
		}
	}

	if (m_playerVel.y <= 0) {
		// top left&& top right
		if (m_pMap->GetTileSymbol(newPlayerPos.x + 0.0f, newPlayerPos.y + 0.0f) != L'.'
			|| m_pMap->GetTileSymbol(newPlayerPos.x + 0.9f, newPlayerPos.y + 0.0f) != L'.') {
			newPlayerPos.y = (int)newPlayerPos.y + 1;
			m_playerVel.y = 0;
		}
	}
	else {
		if (m_pMap->GetTileSymbol(newPlayerPos.x + 0.0f, newPlayerPos.y + 1.0f) != L'.'
			|| m_pMap->GetTileSymbol(newPlayerPos.x + 0.9f, newPlayerPos.y + 1.0f) != L'.') {
			newPlayerPos.y = (int)newPlayerPos.y;
			m_playerVel.y = 0;
		}
	}

	m_playerPos = newPlayerPos;


	// anim
	//if (m_playerVel.x > 0) {
	//	m_playerFrame += deltaTime * 3.0f;
	//}
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
	if (fOffsetY > m_pMap->nLevelHeight - nVisibleTilesY) fOffsetY = m_pMap->nLevelHeight - nVisibleTilesY;

	float fTileOffsetX = (fOffsetX - (int)fOffsetX)* nTileWidth;
	float fTileOffsetY = (fOffsetY - (int)fOffsetY)* nTileWidth;

	// the display size
	SDL_Rect r {0, 0, PIXEL_SCALE * PIXEL_RESOLUTION, PIXEL_SCALE * PIXEL_RESOLUTION };
	SDL_Rect c {0, 0, PIXEL_SCALE * PIXEL_RESOLUTION, PIXEL_SCALE * PIXEL_RESOLUTION };
	// the clip pos in the sprite sheet.

	// render tile
	for (int x = -1; x < nVisibleTilesX + 1; x++){
		for (int y = -1; y < nVisibleTilesY + 1; y++){
			wchar_t tileSymbol = m_pMap->GetTileSymbol(x + fOffsetX, y + fOffsetY);
			if (tileSymbol == L' ') continue;

			const Tile* tile = m_pMap->GetTileData(tileSymbol);

			for (auto s : tile->GetSprites()) {
				RenderSprite(s,
					static_cast<int>(x * nTileWidth - fTileOffsetX),
					static_cast<int>(y * nTileHeight - fTileOffsetY));
			}

		}
	}

	// render player
	const Sprite* s = m_pAssetManager->GetSprite("hero_right");
	//if (m_playerFrame > 3) {
	//	m_playerFrame -= 3;
	//}
	//int frame = static_cast<int>(m_playerFrame);
	//SDL_Log("%d", frame);

	RenderSprite(m_pAssetManager->GetSprite("hero_right"),
		static_cast<int>((m_playerPos.x - fOffsetX) * nTileWidth),
		static_cast<int>((m_playerPos.y - fOffsetY) * nTileHeight));

	//swprintf_s(s, 256, L"SimpleRPG - %s - FPS: %3.2f", 1.0f / deltaTime);

	SDL_RenderPresent(m_pRenderer);

}

void Engine::RenderSprite(const Sprite *s, int xPos, int yPos) {
	SDL_Rect r {xPos,yPos, s->GetWidth(), s->GetHeight() };
	SDL_Rect c = {
		s->GetClipX() * PIXEL_RESOLUTION,  s->GetClipY() * PIXEL_RESOLUTION,
		PIXEL_RESOLUTION, PIXEL_RESOLUTION };

	SDL_RenderCopy(m_pRenderer, s->GetTexture(), &c, &r);
	//SDL_RenderCopyEx(m_pRenderer, s->GetTexture(), &c, &r, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

}

void Engine::LoadData() {
	m_pAssetManager = new AssetManager(m_pRenderer);
	m_pAssetManager->LoadSpriteSheet("Asset/tile64.png", "tileset");
	m_pAssetManager->LoadSpriteSheet("Asset/char64.png", "hero");
	m_pAssetManager->SetSpriteFromSpriteSheet("grass", "tileset", 0, 0);
	m_pAssetManager->SetSpriteFromSpriteSheet("bush", "tileset", 0, 5);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_1", "tileset", 0, 1);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_2", "tileset", 1, 1);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_3", "tileset", 0, 2);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_4", "tileset", 1, 2);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_5", "tileset", 0, 3);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_6", "tileset", 1, 3);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_7", "tileset", 0, 4);
	m_pAssetManager->SetSpriteFromSpriteSheet("tree_8", "tileset", 1, 4);


	m_pAssetManager->SetSpriteFromSpriteSheet("hero_right", "hero", 0, 11);

	m_playerPos = Vec2(10, 10);

	m_pInputSystem = new InputSystem();
	m_pMap = new Map(m_pAssetManager);

}


void Engine::UnloadData() {
	delete m_pAssetManager;
	delete m_pMap;
	delete m_pInputSystem;
}