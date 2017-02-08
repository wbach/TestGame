#include "../GameEngine/Engine/Engine.h"

int main(int argc, char* argv[])
{
	CEngine engine("Test Game - Open GL", 640, 480, false);
	engine.GameLoop();
}