#include <iostream>
#include <string>

#include <windows.h>

#include "color.h"
#include "console.h"

#include "game.h"

using namespace std;

game core;

int main()
{
	console::setup();
	core = game();
	
	//console::print("{C=GRAY}I don't want to stay here any longer, the door opens after just one small push, as I step inside the door closes. {D=0}IT'S{D=1000} {D=0}A{D=1000} {D=280}TRAP!{D=30}, A flaming skull with spider limbs jumps down from the ceiling.\n", true);

	system("PAUSE");

	return 0;
}

