#ifndef CONSOLE_H
#define CONSOLE_H

class console
{
public:
	static void setup();

	static void print(std::string s, bool parse = true);
	static void printraw(std::string s);

	static int getWidth();
	static int getHeight();

	static void setCursor(int x, int y);
};

#endif // !CONSOLE_H
