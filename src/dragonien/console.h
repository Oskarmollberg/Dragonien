#ifndef CONSOLE_H
#define CONSOLE_H

class console
{
public:
	static void setup();
	static void print(std::string text, bool parse = true);
};

#endif // !CONSOLE_H
