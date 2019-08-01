#pragma once
#include <string>

class Map {
public:
	std::wstring sLevel;
	int nLevelWidth;
	int nLevelHeight;

public:
	Map() {
		nLevelWidth = 16;
		nLevelHeight = 16;

		sLevel += L"................";
		sLevel += L"................";
		sLevel += L"................";
		sLevel += L"................";
		sLevel += L"...#..#.#.......";
		sLevel += L"..#.............";
		sLevel += L"..#.............";
		sLevel += L"..##########.#..";
		sLevel += L"...........#....";
		sLevel += L"...........#....";
		sLevel += L"...........#....";
		sLevel += L"................";
		sLevel += L"................";
		sLevel += L"................";
		sLevel += L"................";
		sLevel += L"................";

	}

	wchar_t GetTile(int x, int y) {
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
			return sLevel[y * nLevelWidth + x];
		}
		else {
			return L' ';
		}
	};

	void SetTile(int x, int y, wchar_t c) {
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
			 sLevel[y * nLevelWidth + x] = c;
		}
	};
};