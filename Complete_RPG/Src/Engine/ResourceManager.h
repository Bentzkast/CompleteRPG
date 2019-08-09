#pragma once
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "Sprite.h"

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
		bool LoadBinary(const std::string& filepath, char* buffer, int size);
		bool SaveBinary(const std::string& filepath, char* buffer, int size);
	private:
		std::unordered_map<std::string, Sprite*> m_MapSprites;
		SDL_Renderer* m_pRenderer;
	};
}