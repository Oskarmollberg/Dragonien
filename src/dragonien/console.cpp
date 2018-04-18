#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include <windows.h>

#include <algorithm>

#include "color.h"
#include "console.h"

static HWND window;		//Console handle
static HDC hdc;			// Device Context handle

static HANDLE hstdin;	// Console Handle In
static HANDLE hstdout;	// Console Handle Out

const int DEFAULT_DELAY_MS = 30;

const color DEFAULT_COLOR_FOREGROUND = color::WHITE;
const color DEFAULT_COLOR_BACKGROUND = color::BLACK;

void console::setup()
{
	window	= GetConsoleWindow();
	hdc		= GetDC(window);

	hstdin	= GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

void console::print(std::string s, bool parse)
{
	std::string command("");
	std::string value("");

	int delay = 0;

	int index = 0;
	if (parse)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
		loop:
			if (s[i] == '{')
			{
				i++;

				for (size_t j = i; j < s.size(); j++)
				{
					if (s[j] == '}')
					{
						i++;
						j++;

						value = "";
						goto loop;
					}
					else if (s[j] == '=')
					{
						i++;
						j++;
						for (size_t k = j; k < s.size(); k++)
						{
							if (s[k] == '}')
							{
								i++;
								goto loop;
							}

							value.push_back(s[k]);
							i++;
							j++;
						}
					}
					else
					{
						command.push_back(s[j]);
						i++;
					}
				}
			}
			else
			{
				std::transform(command.begin(), command.end(), command.begin(), ::toupper);	// Convers command to uppercase.
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
				else if (command == "D" || command == "DELAY")
				{
					delay = std::stoi(value, nullptr, 10);
				}
				else if (command == "S" || command == "SLEEP")
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(value)));
				}
				else if (command == "R")
				{
					if (value == "")			// Resets all effects.
					{
						SetConsoleTextAttribute(hstdout, DEFAULT_COLOR_FOREGROUND + (DEFAULT_COLOR_BACKGROUND << 4));
					}
					else if (value == "COLOR")	// Resets color.
					{
						SetConsoleTextAttribute(hstdout, DEFAULT_COLOR_FOREGROUND + (DEFAULT_COLOR_BACKGROUND << 4));
					}
				}

				std::cout << s[i];
				index++;

				command = "";		// Resets command string.
				value = "";			// Resets value string.

				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
		}
	}
	else
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			std::cout << s[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}
}
void console::printraw(std::string s)
{
	std::cout << s;
}

int console::getWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	return (csbi.srWindow.Right - csbi.srWindow.Left) + 1;
}

int console::getHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	return (csbi.srWindow.Bottom - csbi.srWindow.Top) + 1;
}

void console::setCursor(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(hstdout, pos);
}
