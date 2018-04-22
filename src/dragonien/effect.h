#ifndef EFFECT_H
#define EFFECT_H

struct effect
{
public:
	effect();
	effect(int index, std::string command, std::string value);

	int index;
	std::string command;
	std::string value;
};

#endif // !EFFECT_H
