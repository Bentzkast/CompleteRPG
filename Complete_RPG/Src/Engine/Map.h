#pragma once
#include <string>
class Map
{
public:
	Map();
	~Map();
	std::string name;
	int nWidth;
	int nHeight;

	char GetIndex(int x, int y);
	char GetSolid(int x, int y);

	bool CreateDummy(int width, int height, const std::string map);
	bool LoadMap(const std::string& filepath);
	bool SaveMap();
private:
	char* mIndices;
	char* mSolids;
};