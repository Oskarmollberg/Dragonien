#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include "effect.h"

class console
{
public:
	static void setup();
	
	static void command(std::string command, int value);
	static void command(std::string command, std::string value);

	static void parse(std::string &s, std::vector<effect> &effects);

	static void print(std::string s, bool parse = true);
	static void printraw(std::string s);

	static void showCursor(bool b);

	static int getWidth();
	static int getHeight();

	static void setCursorPosition(int x, int y);
};

#endif // !CONSOLE_H
