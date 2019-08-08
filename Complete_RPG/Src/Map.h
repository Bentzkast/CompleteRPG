#pragma once
#include <string>

struct Tile {
private:
	wchar_t m_symbol;
	bool m_solid;
	std::vector<const Sprite*>  m_Sprites;
public:
	Tile(wchar_t symbol, bool solid) :
		m_symbol(symbol),
		m_solid(solid){}

	~Tile() {

	}

	void AddSprite(const Sprite* sprite) {
		m_Sprites.emplace_back(sprite);
	}

	const wchar_t GetSymbol() const { return m_symbol; }
	const bool GetIsSolid() const { return m_solid; }
	const std::vector<const Sprite*>& GetSprites() const { return m_Sprites; }
};

class Map {
private:
	const AssetManager* const m_AssetManager;
	std::unordered_map<wchar_t, Tile* > m_mapTileTypes;
public:
	std::wstring sLevel;
	int nLevelWidth;
	int nLevelHeight;
	

public:
	Map(const AssetManager* const assetManager): m_AssetManager(assetManager){
		nLevelWidth = 32;
		nLevelHeight = 16;

		// todo load from json

		sLevel += L"............#...................";
		sLevel += L"............#...................";
		sLevel += L"............#...................";
		sLevel += L"............#######.............";
		sLevel += L"##................#.............";
		sLevel += L"12#................########.....";
		sLevel += L"872#...#..................#.....";
		sLevel += L"784.......................#.....";
		sLevel += L"872.......................#.....";
		sLevel += L"784.......................#.....";
		sLevel += L"872#...#.............#...#......";
		sLevel += L"784#....................#.......";
		sLevel += L"872#...................#........";
		sLevel += L"7872#...####......#####.........";
		sLevel += L"8787212121212#..###12121212.....";
		sLevel += L"7878787878784#..###37878784.....";

		Tile* t = new Tile(L'.', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		m_mapTileTypes.emplace(L'.', t);

		t = new Tile(L'#', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("bush"));
		m_mapTileTypes.emplace(L'#', t);

		t = new Tile(L'1', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_1"));
		m_mapTileTypes.emplace(L'1', t);

		t = new Tile(L'2', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_2"));
		m_mapTileTypes.emplace(L'2', t);

		t = new Tile(L'3', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_3"));
		m_mapTileTypes.emplace(L'3', t);

		t = new Tile(L'4', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_4"));
		m_mapTileTypes.emplace(L'4', t);

		t = new Tile(L'5', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_5"));
		m_mapTileTypes.emplace(L'5', t);

		t = new Tile(L'6', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_6"));
		m_mapTileTypes.emplace(L'6', t);

		t = new Tile(L'7', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_7"));
		m_mapTileTypes.emplace(L'7', t);

		t = new Tile(L'8', false);
		t->AddSprite(m_AssetManager->GetSprite("grass"));
		t->AddSprite(m_AssetManager->GetSprite("tree_8"));
		m_mapTileTypes.emplace(L'8', t);
	}

	~Map() {
		for (auto s : m_mapTileTypes) {
			delete s.second;
		}
		m_mapTileTypes.clear();
	}

	wchar_t GetTileSymbol(int x, int y) {
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
			return sLevel[y * nLevelWidth + x];
		}
		else {
			return L' ';
		}
	};

	const Tile* GetTileData(const wchar_t& name) const {
		if (name == L' ') return nullptr;
		auto iter = m_mapTileTypes.find(name);
		if (iter != m_mapTileTypes.end()) {
			return iter->second;
		}
		//wprintf(L"%s\n", name);
		//SDL_Log("No %s such tile!", name);

		return nullptr;
	}


	void SetTile(int x, int y, wchar_t c) {
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
			 sLevel[y * nLevelWidth + x] = c;
		}
	};
};