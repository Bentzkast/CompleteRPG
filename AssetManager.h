#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include "Constant.h"

class Sprite {
public:
	Sprite(std::string name, SDL_Texture* texture) :
		m_name(name)
	{
		m_pTexture = texture;
		//SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_width, &m_height);
		m_width = PIXEL_SCALE * PIXEL_RESOLUTION;
		m_height = PIXEL_SCALE * PIXEL_RESOLUTION;
	}
	~Sprite() {
		SDL_DestroyTexture(m_pTexture);
	}
public:
	const std::string GetName() const { return m_name; }
	SDL_Texture* GetTexture() const { return m_pTexture; }
	const int GetWidth() const { return m_width; }
	const int GetHeight() const { return m_height; }
private:
	std::string m_name;
	int m_width;
	int m_height;
	SDL_Texture* m_pTexture;
};

class AssetManager {
public:
	AssetManager(SDL_Renderer* renderer);
	~AssetManager();

public:
	bool LoadSpriteSheet(const std::string& filepath, const std::string& name);
	const Sprite* GetSprite(const std::string& name) const;

private:
	std::unordered_map<std::string, Sprite*> m_mapSprites;
	SDL_Renderer* m_renderer;
};

