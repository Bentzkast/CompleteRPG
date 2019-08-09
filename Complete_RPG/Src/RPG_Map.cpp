#include "RPG_Map.h"



RPG_Map::RPG_Map():
	pSprite(nullptr),
	Width(0),
	Height(0),
	m_pSolids(nullptr),
	m_pIndices(nullptr)
{

}


RPG_Map::~RPG_Map()
{
	delete[] m_pSolids;
	delete[] m_pIndices;
}
