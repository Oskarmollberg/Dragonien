#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include <windows.h>

#include <algorithm>
#include <vector>

#include "color.h"
#include "console.h"

#include "util.h"
#include "effect.h"


static HWND window;		//Console handle
static HDC hdc;			// Device Context handle

static HANDLE hstdin;	// Console Handle In
static HANDLE hstdout;	// Console Handle Out

const int DEFAULT_DELAY_MS = 30;

const color DEFAULT_COLOR_FOREGROUND = color::WHITE;
const color DEFAULT_COLOR_BACKGROUND = color::BLACK;

int delay = DEFAULT_DELAY_MS;

void console::setup()
{
	window	= GetConsoleWindow();
	hdc		= GetDC(window);

	hstdin	= GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

void console::command(std::string command, int value)
{
	console::command(command, std::to_string(value));
}
void console::command(std::string command, std::string value)
{
	std::transform(command.begin(), command.end(), command.begin(), ::toupper);	// Converts command to uppercase.
	if		(command == "C" || command == "COLOR" || command == "COLOUR")
	{
		SetConsoleTextAttribute(hstdout, std::stoi(value));
	}
	else if (command == "D" || command == "DELAY")
	{
		delay = std::stoi(value, nullptr, 10);
	}
	else if (command == "S" || command == "SLEEP")
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(value)));
	}
	else if (command == "R" || command == "RESET")
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
}

void console::parse(std::string &s, std::vector<effect> &effects)
{
	std::string command("");
	std::string value("");

	std::string result;

	int index = 0;

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

					effects.push_back(effect());

					effects[effects.size() - 1].index = index;
					effects[effects.size() - 1].command = command;
					effects[effects.size() - 1].value = value;

					command = "";
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

							effects.push_back(effect());

							effects[effects.size() - 1].index = index;
							effects[effects.size() - 1].command = command;
							effects[effects.size() - 1].value = value;

							command = "";
							value = "";

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
			if(i < s.size())
				result.push_back(s[i]);
		}

		index++;
	}

	s = result;
}

void console::print(std::string s, bool parse)
{
	std::string command("");
	std::string value("");

	std::vector<effect> effects;

	console::parse(s, effects);

	if (s.empty())		// If	: The string only consists of commands ~ apply them.
	{					// Else	: Print the string using the effects at correct indexes.
		for (const effect& effect : effects)
		{
			console::command(effect.command, effect.value);
		}
	}
	else
	{
		for (int i = 0; i < s.size(); i++)
		{
			std::vector<effect> effects_to_apply;

			std::copy_if(effects.begin(), effects.end(), std::back_inserter(effects_to_apply), [&](const effect & item)
			{
				return item.index == i;
			});

			for (const effect& effect : effects_to_apply)
			{
				console::command(effect.command, effect.value);
			}

			std::cout << s[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}
}
void console::printraw(std::string s)
{
	std::cout << s;
}

void console::showCursor(bool b)
{
	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(hstdout, &info);
	info.bVisible = b;
	SetConsoleCursorInfo(hstdout, &info);
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

void console::setCursorPosition(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(hstdout, pos);
}
