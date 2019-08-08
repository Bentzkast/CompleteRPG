#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include "Constant.h"

class Sprite {
public:
	Sprite(std::string name, SDL_Texture* texture, int clipX, int clipY) :
		m_name(name), m_clipX(clipX), m_clipY(clipY)
	{
		m_pTexture = texture;
		//SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_width, &m_height);
		m_width = PIXEL_SCALE * PIXEL_RESOLUTION;
		m_height = PIXEL_SCALE * PIXEL_RESOLUTION;
	}
	~Sprite() {
		//SDL_DestroyTexture(m_pTexture);
	}
public:
	const std::string GetName() const { return m_name; }
	SDL_Texture* GetTexture() const { return m_pTexture; }
	const int GetWidth() const { return m_width; }
	const int GetHeight() const { return m_height; }
	const int GetClipX() const { return m_clipX; }
	const int GetClipY() const { return m_clipY; }

private:
	std::string m_name;
	int m_width;
	int m_height;
	int m_clipX;
	int m_clipY;
	SDL_Texture* m_pTexture;
};

class AssetManager {
public:
	AssetManager(SDL_Renderer* renderer);
	~AssetManager();

public:
	bool LoadSpriteSheet(const std::string& filepath, const std::string& name);
	const Sprite* GetSprite(const std::string& name) const;
	void SetSpriteFromSpriteSheet(const std::string& name, const std::string& sheetName,
		int clipX, int clipY);

private:
	std::unordered_map<std::string, SDL_Texture*> m_mapSpritesSheet;
	std::unordered_map<std::string, Sprite*> m_mapSprites;
	SDL_Renderer* m_renderer;
};

