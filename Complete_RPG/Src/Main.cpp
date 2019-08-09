#include "Engine/Core.h"
#include "Engine/Color.h"
#include "Engine/Sprite.h"


class RPG : public Engine::Game
{
public:
	RPG()
	{}

public:
	bool OnGameStart() override
	{
		SDL_Log("Game Start");
		LoadSprite("Asset/char64.png", "hero");
		SDL_Log(buffer);
		return true;
	}

	bool OnUpdate(float deltaTime) override
	{
		Clear(Engine::GREY);
		if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_L) == Engine::EReleased)
		{
			LoadBinary("Asset/test.txt", buffer, 10);
		}
		if (GetInputState().Keyboard.GetKeyState(SDL_SCANCODE_S) == Engine::EReleased)
		{
			SaveBinary("Asset/test.txt", buffer, 10);
		}
		const Engine::Sprite* heroSprite = GetSprite("hero");
		Engine::Vec2 pos = Engine::Vec2(100, 100);
		SDL_Rect clip{ 0, 11 * 64, 64, 64 };
		//DrawSprite(heroSprite, pos);
		DrawPartialSprite(heroSprite, pos, &clip);

		return true;
	}

	bool OnGameDestroy() override
	{
		SDL_Log("Game Destroyed");
		return true;
	}
private:
	char buffer[10];
};


int main(int argc, char** argv) {

	RPG rpg;
	if (rpg.Construct("Simple RPG", 1024, 768, false))
	{
		rpg.Start();
	}

	return 0; 
}