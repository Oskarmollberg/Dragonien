#ifndef CONSOLE_H
#define CONSOLE_H

class console
{
public:

	static void setup();
	static void print(std::string text, bool parse = true);

	static void setColor(int c);
	static void setColor(color c);
};

#endif // !CONSOLE_H
