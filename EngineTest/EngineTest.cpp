#include <iostream>
#include "TestGame.h"
#include <string>
#include "GravityGame.h"

using namespace Engine2d;

void testGame() {
	TestGame tg(800, 600);
	tg.Run();
}

void gravity() {
	GravityGame gg;
	gg.Run();
}

int main(int argc, char** argv)
{
	gravity();
    return 0;
}