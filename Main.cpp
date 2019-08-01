#include "Engine.h"

int main(int argc, char** argv) {

	
	Engine engine;
	if (engine.Init() == false) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init Game");
		return 1;
	}

	engine.LoadData();
	engine.Run();
	engine.UnloadData();
	engine.Close();

	return 0; 
}