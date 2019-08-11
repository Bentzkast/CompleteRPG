#include "ResourceManager.h"
#include <SDL_image.h>

namespace Engine
{
	ResourceManager::ResourceManager(SDL_Renderer* renderer) : m_pRenderer(renderer) {

	}

	ResourceManager::~ResourceManager() {
		for (auto s : m_MapSprites) {
			delete s.second;
		}
		m_MapSprites.clear();
	}

	const Sprite* ResourceManager::GetSprite(const std::string& name) const
	{
		auto iter = m_MapSprites.find(name);
		if (iter != m_MapSprites.end()) {
			return iter->second;
		}
		SDL_Log("No %s Sprite!", name);

		return nullptr;
	}

	bool ResourceManager::LoadSprite(const std::string& filepath, const std::string& name) {
		// only load single image for now;

		// TODO check is sheet with same name exist
		SDL_Texture* tex = nullptr;

		SDL_Surface* surf = IMG_Load(filepath.c_str());
		if (!surf)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("[ResourceManager] Failed to load texture file %s", filepath.c_str()));
			return false;
		}
		tex = SDL_CreateTextureFromSurface(m_pRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("[ResourceManager] Failed to convert surface to texture file %s", filepath.c_str()));
			return false;
		}
		m_MapSprites.emplace(name.c_str(), new Sprite(name.c_str(),tex));

		SDL_Log("[ResourceManager] Loaded %s from successfully", name.c_str(), filepath.c_str());
		return true;
	}

	bool ResourceManager::LoadBinary(const std::string& filepath, int* buffer, int size, int offset)
	{
		SDL_RWops* file = SDL_RWFromFile(filepath.c_str(), "r+b");
		if (file == nullptr)
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, ("[ResourceManager] Unable to open file %s", filepath.c_str()));
			return false;
		}
		else
		{
			SDL_Log("[ResourceManager] Reading File...");
			for (int i = offset; i < size; i++)
			{
				SDL_RWread(file, &buffer[i], sizeof(int), 1);
			}
			SDL_RWclose(file);
		}

		return true;
	}

	bool ResourceManager::SaveBinary(const std::string& filepath, int* buffer, int size,int offset)
	{
		SDL_RWops* file = SDL_RWFromFile(filepath.c_str(), "r+b");
		if (file == nullptr)
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, ("[ResourceManager] Unable to find file %s", filepath.c_str()));

			file = SDL_RWFromFile(filepath.c_str(), "w+b");

			if (file == nullptr)
			{
				SDL_LogError(SDL_LOG_CATEGORY_ERROR, ("[ResourceManager] Unable to Create file! %s , SDL_ERROR:%s", filepath.c_str(), SDL_GetError()));
				return false;
			}
			SDL_Log("[ResourceManager] New Empty file created");
		}

		SDL_Log("[ResourceManager] Writing to File...");
		for (int i = offset; i < size; i++)
		{
			SDL_RWwrite(file, &buffer[i], sizeof(int), 1);
		}
		SDL_RWclose(file);

		return true;
	}
}