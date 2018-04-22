#ifndef UTIL_H
#define UTIL_H

class util
{
	template<typename Out>
	static void split(const std::string &s, char delim, Out result)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			*(result++) = item;
		}
	}

public:
	static std::vector<std::string> split(std::string &s, char delim);
};

#endif // !UTIL_H
