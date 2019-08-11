#pragma once
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "Sprite.h"
#include "Map.h"

namespace Engine
{
	class ResourceManager
	{
	public:
		ResourceManager(SDL_Renderer* renderer);
		~ResourceManager();
	
	public:
		bool LoadSprite(const std::string& filepath, const std::string& name);
		const Sprite* GetSprite(const std::string& name) const;

	public:
		bool LoadBinary(const std::string& filepath, int* buffer, int size, int offset = 0);
		bool SaveBinary(const std::string& filepath, int* buffer, int size, int offset = 0);
		
	private:
		std::unordered_map<std::string, Sprite*> m_MapSprites;
		SDL_Renderer* m_pRenderer;
	};
}