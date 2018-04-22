#include <vector>
#include <string>

#include <sstream>
#include <iterator>

#include "util.h"

std::vector<std::string> util::split(std::string & s, char delim)
{
	std::vector<std::string> elements;
	split(s, delim, std::back_inserter(elements));
	return elements;
}
