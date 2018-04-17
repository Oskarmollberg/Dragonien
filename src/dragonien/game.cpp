#include <string>
#include <fstream>
#include <streambuf>

#include "game.h"
#include "console.h"

game::game()
{
	std::ifstream t("C:\\Users\\edvin.hansson1.LEARNET\\Documents\\bee.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	console::print(str, true);
}

game::~game()
{
}

void game::exit()
{
}
