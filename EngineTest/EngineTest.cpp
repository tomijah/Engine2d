#include <iostream>
#include "TestGame.h"
#include <string>

using namespace Engine2d;

void game() {
	TestGame gb(800, 600);
	gb.Run();
}

int main(int argc, char** argv)
{
	game();
    return 0;
}