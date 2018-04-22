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

game core;

void display()
{
	image img(string("0000011101110111011101110000000001110010011010000110001001110000011100100010001000100010011100000000011101110111011101110000000000000000000001000000000000000000001101010000010100000101001100000000001101000101010000110000000000000000001100110011000000000000"));


	int posX = 10;	// Start position(X) to draw image from.
	int posY = 10;	// Start position(Y) to draw image from.

	for (int y = 8; y > 0; y--)					// Prints out the whole image. Function will later be moved to a display.cpp function.
	{
		for (int x = 8; x > 0; x--)
		{
			int v = img.getPixelData(x, y);		// Gets data from image pixel. Data includes - Color index...

			console::setCursorPosition(posX, posY);

			switch (v)							// Used like a palette. ONLY TEMPORARY!!!
			{
			case 0:
				console::print("{C=BLACK}");
				break;
			case 1:
				console::print("{C=GRAY}");
				break;
			case 2:
				console::print("{C=WHITE}");
				break;
			case 3:
				console::print("{C=DARKGREEN}");
				break;
			case 4:
				console::print("{C=GREEN}");
				break;
			case 5:
				console::print("{C=GREEN}");
				break;
			case 6:
				console::print("{C=RED}");
				break;
			case 7:
				console::print("{C=BROWN}", true);
				break;
			case 8:
				console::print("{C=YELLOW}", true);
				break;
			default:
				break;
			}
			console::print("\xDB");
			posX += 2;
		}
		cout << endl;
		posY++;
		posX -= img.getWidth() * 2;
	}
}

int main()
{
	console::setup();
	console::showCursor(false);

	core = game();
	
	//console::print("{c=0xE}I don't want to stay here any longer, the door opens after just one small push, as I step inside the door closes.\n{D=0}IT'S{D=1000} {D=0}A{D=1000} {D=280}TRAP!{D=30}, A flaming skull with spider limbs jumps down from the ceiling.\n", true);
	//system("PAUSE");

	int yPos = 10;
	int xPos = 10;

	while (true)
	{
		image img(string("0000011101110111011101110000000001110010011010000110001001110000011100100010001000100010011100000000011101110111011101110000000000000000000001000000000000000000001101010000010100000101001100000000001101000101010000110000000000000000001100110011000000000000"));

		

		console::command("d", "0");

		for (int y = 1; y <= 8; y+=2)
		{
			for (int x = 1; x <= 8; x++)
			{
				console::setCursorPosition(xPos + x, yPos + y/2);

				// Combine colors before printing.

				int foreground_value = img.getPixelData(x, y);
				int background_value = img.getPixelData(x, y + 1);

				color foreground_color;
				color background_color;

				switch (foreground_value)							// Used like a palette. ONLY TEMPORARY!!!
				{
				case 0:
					foreground_color = color::BLACK;
					break;
				case 1:
					foreground_color = color::GRAY;
					break;
				case 2:
					foreground_color = color::WHITE;
					break;
				case 3:
					foreground_color = color::DARK_GREEN;
					break;
				case 4:
					foreground_color = color::GREEN;
					break;
				case 5:
					foreground_color = color::GREEN;
					break;
				case 6:
					foreground_color = color::RED;
					break;
				case 7:
					foreground_color = color::BROWN;
					break;
				case 8:
					foreground_color = color::YELLOW;
					break;
				default:
					break;
				}
				switch (background_value)							// Used like a palette. ONLY TEMPORARY!!!
				{
				case 0:
					background_color = color::BLACK;
					break;
				case 1:
					background_color = color::GRAY;
					break;
				case 2:
					background_color = color::WHITE;
					break;
				case 3:
					background_color = color::DARK_GREEN;
					break;
				case 4:
					background_color = color::GREEN;
					break;
				case 5:
					background_color = color::GREEN;
					break;
				case 6:
					background_color = color::RED;
					break;
				case 7:
					background_color = color::BROWN;
					break;
				case 8:
					background_color = color::YELLOW;
					break;
				default:
					break;
				}

				console::command("color", to_string(foreground_color + (background_color << 4)));
				console::print("\xDF");
			}
		}

		yPos += 9;
		//system("PAUSE");
	}
	return 0;
}

