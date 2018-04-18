#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <windows.h>

#include "color.h"
#include "console.h"

#include <bitset>

#include "game.h"
#include "image.h"

using namespace std;

game core;

int main()
{
	console::setup();
	core = game();
	
	//console::print("{C=GRAY}I don't want to stay here any longer, the door opens after just one small push, as I step inside the door closes.\n{D=0}IT'S{D=1000} {D=0}A{D=1000} {D=280}TRAP!{D=30}, A flaming skull with spider limbs jumps down from the ceiling.\n", true);


	while (true)
	{
		system("cls");

		/*
		console::setCursor(0, 0);
		console::printraw("\xDC");

		console::setCursor(0, 1);
		console::print("{C=RED}\xDC", true, 0);

		console::setCursor(0, 1);
		console::print("{C=RED}\xDF", true, 0);

		console::setCursor(0, console::getHeight() - 1);
		console::printraw("\xDB");

		console::setCursor(console::getWidth() - 1, console::getHeight() - 1);
		console::printraw("\xDB");
		*/

		/*
		
			Setting the background color of a half-cube will change the other side of the cube!


			
		*/


		image img(string("0000011101110111011101110000000001110010011010000110001001110000011100100010001000100010011100000000011101110111011101110000000000000000000001000000000000000000001101010000010100000101001100000000001101000101010000110000000000000000001100110011000000000000"));
		
		std::stringstream s;
		int c = color::WHITE + (color::BLUE << 4);
		s << std::hex << c;
		console::print("{C=" + s.str() + "}\xDF");

		int posX = 10;	// Start position(X) to draw image from.
		int posY = 10;	// Start position(Y) to draw image from.

		for (int y = 8; y > 0; y--)					// Prints out the whole image. Function will later be moved to a display.cpp function.
		{
			for (int x = 8; x > 0; x--)
			{
				int v = img.getPixelData(x, y);		// Gets data from image pixel. Data includes - Color index...

				console::setCursor(posX, posY);

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
				posX+=2;
			}
			cout << endl;
			posY++;
			posX-=img.getWidth() * 2;
		}

		cin.get();
	}

	return 0;
}

