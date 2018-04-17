#include <iostream>
#include <string>

#include <windows.h>

#include "color.h"
#include "console.h"


static HWND window;

static HANDLE hstdin;
static HANDLE hstdout;

const color DEFAULT_COLOR_FOREGROUND = color::WHITE;
const color DEFAULT_COLOR_BACKGROUND = color::BLACK;

void console::setup()
{
	window = GetConsoleWindow();

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

void console::print(std::string text, bool parse)
{
	std::string command("");
	std::string value("");

	int index = 0;
	if (parse)
	{
		for (int i = 0; i < text.size(); i++)
		{
		loop:
			if (text[i] == '{')
			{
				i++;

				for (int j = i; j < text.size(); j++)
				{
					if (text[j] == '}')
					{
						i++;
						j++;

						value = "";
						goto loop;
					}
					else if (text[j] == '=')
					{
						i++;
						j++;
						for (int k = j; k < text.size(); k++)
						{
							if (text[k] == '}')
							{
								i++;
								goto loop;
							}

							value.push_back(text[k]);
							i++;
							j++;
						}
					}
					else
					{
						command.push_back(text[j]);
						i++;
					}
				}
			}
			else
			{
				int abs = 0;
				if (command == "C" || command == "COLOR" || command == "COLOUR")
				{
					int v = 0;

					if (value == "DEFAULT")
						v = DEFAULT_COLOR_FOREGROUND;
					else if (value == "BLACK")
						v = color::BLACK;
					else if (value == "DARK_BLUE" || value == "DARKBLUE")
						v = color::DARK_BLUE;
					else if (value == "DARK_GREEN" || value == "DARKGREEN")
						v = color::DARK_GREEN;
					else if (value == "DARK_CYAN" || value == "DARKCYAN")
						v = color::DARK_CYAN;
					else if (value == "DARK_RED" || value == "DARKRED")
						v = color::DARK_RED;
					else if (value == "DARK_MAGENTA" || value == "DARKMAGENTA")
						v = color::DARK_MAGENTA;
					else if (value == "BROWN")
						v = color::BROWN;
					else if (value == "LIGHT_GRAY" || value == "LIGHTGRAY")
						v = color::LIGHT_GRAY;
					else if (value == "GRAY")
						v = color::GRAY;
					else if (value == "BLUE")
						v = color::BLUE;
					else if (value == "GREEN")
						v = color::GREEN;
					else if (value == "CYAN")
						v = color::CYAN;
					else if (value == "RED")
						v = color::RED;
					else if (value == "MAGENTA")
						v = color::MAGENTA;
					else if (value == "YELLOW")
						v = color::YELLOW;
					else if (value == "WHITE")
						v = color::WHITE;
					else
						v = std::stoul(value, nullptr, 16);

					SetConsoleTextAttribute(hstdout, v);
				}
				else if (command == "R")
				{
					SetConsoleTextAttribute(hstdout, DEFAULT_COLOR_FOREGROUND + (DEFAULT_COLOR_BACKGROUND << 4));
				}
				std::cout << text[i];
				index++;

				command = "";
				value = "";
			}
		}
	}
	else
	{
		std::cout << text;
	}
}

void console::setColor(int c)
{
	SetConsoleTextAttribute(hstdout, c);
}
void console::setColor(color c)
{
	SetConsoleTextAttribute(hstdout, c);
}
