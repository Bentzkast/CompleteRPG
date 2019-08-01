#include "AssetManager.h"

AssetManager::AssetManager(SDL_Renderer* renderer) : m_renderer(renderer) {
	
}
AssetManager::~AssetManager() {
	for (auto s : m_mapSprites) {
		delete s.second;
	}
	m_mapSprites.clear();
}

const Sprite* AssetManager::GetSprite(const std::string& name) const {
	auto iter = m_mapSprites.find(name);
	if (iter != m_mapSprites.end()) {
		return iter->second;
	}
	SDL_Log("No %s Sprite!", name);

	return nullptr;
}


bool AssetManager::LoadSpriteSheet(const std::string& filepath, const std::string& name) {
	// only load single image for now;

	// TODO check is sheet with same name exist
	SDL_Texture* tex = nullptr;

	SDL_Surface* surf = IMG_Load(filepath.c_str());
	if (!surf)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("Failed to load texture file %s", filepath.c_str()));
		return false;
	}
	tex = SDL_CreateTextureFromSurface(m_renderer, surf);
	SDL_FreeSurface(surf);
	if (!tex) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("Failed to conver surface to texture file %s", filepath.c_str()));
		return false;
	}
	m_mapSprites.emplace(name.c_str(), new Sprite(name.c_str(), tex));

	SDL_Log("Loaded %s successfully", name);
	return true;
}
