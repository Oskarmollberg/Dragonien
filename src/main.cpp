#include <iostream>
#include <string>

#include <windows.h>

#include "color.h"
#include "console.h"

using namespace std;

int main()
{
	console::setup();

	console::print("{C=RED}[{C=GREEN}O{C=RED}]{C=WHITE}\n", true);


	system("PAUSE");

	return 0;
}

