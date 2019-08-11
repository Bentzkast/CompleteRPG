#include "Engine/Core.h"
#include "Engine/Color.h"
#include "Engine/Sprite.h"
#include "RPG.h"




int main(int argc, char** argv) {

	RPG rpg;
	if (rpg.Construct("Simple RPG", 1024, 768, false))
	{
		rpg.Start();
	}

	return 0; 
}