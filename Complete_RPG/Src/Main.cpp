#include "Engine/Core.h"
#include "Engine/Color.h"

class RPG : public Engine::Game
{
public:
	RPG()
	{}

public:
	bool OnGameStart() override
	{
		SDL_Log("Game Start");
		return true;
	}

	bool OnUpdate(float deltaTime) override
	{
		Clear(Engine::GREY);
		return true;
	}

	bool OnGameDestroy() override
	{
		SDL_Log("Game Destroyed");
		return true;
	}
};


int main(int argc, char** argv) {

	RPG rpg;
	if (rpg.Construct("Simple RPG", 1024, 768, false))
	{
		rpg.Start();
	}

	return 0; 
}