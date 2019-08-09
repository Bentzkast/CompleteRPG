#pragma once
#include <SDL.h>
#include <string>

namespace Engine
{
	struct Sprite
	{
	public:
		friend class Game;

		Sprite(std::string name, SDL_Texture* texture)
			: Name(name), m_pTexture(texture)
		{
			SDL_QueryTexture(texture, nullptr, nullptr, &Width, &Height);
		}
		~Sprite()
		{
			SDL_DestroyTexture(m_pTexture);
		}
	public:
		std::string Name;

		int Width;
		int Height;
	private:
		SDL_Texture* m_pTexture;

	};

}