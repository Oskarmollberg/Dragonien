#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <windows.h>

#include "color.h"
#include "console.h"

#include "game.h"
#include "image.h"

#include "util.h"

using namespace std;

game core; // Hejealliip

void display()
{
	console::command("d", 0);	// Sets the delay between characters to 0 for displaying image.

	image img
	(
		string("0000011101110111011101110000000001110010011010000110001001110000011100100010001000100010011100000000011101110111011101110000000000000000000001000000000000000000001101010000010100000101001100000000001101000101010000110000000000000000001100110011000000000000"), 
		string("000010001111001010101010110001101110")
	);

	for (int y = 1; y <= 8; y += 2)
	{
		for (int x = 1; x <= 8; x++)
		{
			console::setCursorPosition(10 + x, 10 + y / 2);			// Sets the cursor position according to X and Y positions.

			color foreground_color = img.getPixelData(x, y);		// Gets the upper pixel.
			color background_color = img.getPixelData(x, y + 1);	// Gets the lower pixel.

			console::command("color", foreground_color + (background_color << 4));	// Set the console color.
			console::print("\xDF");									// Print a half-square.
		}
	}
}

int main()
{
	console::setup();
	console::showCursor(false);

	core = game();

	display();

	system("PAUSE");
	return 0;
}

