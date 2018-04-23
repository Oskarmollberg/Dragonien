/*
	image.cpp is used to hold a texture. 

	An image is stored via 'indirect color' with an additional palette for color.
*/


#include <algorithm>
#include <bitset>

#include "color.h"
#include "image.h"

const int BITS_PER_PIXEL = 4;

const int WIDTH	= 8;
const int HEIGHT = 8;

image::image(std::string data, std::string palette)
{
	_data = data;
	_palette = palette;
}

std::string image::getData()
{
	return _data;
}
std::string image::getPalette()
{
	return _palette;
}

color image::getPixelData(int x, int y)
{
	size_t min = ((y - 1) * getWidth() + (x - 1)) * BITS_PER_PIXEL;
	size_t max = min + BITS_PER_PIXEL;

	int index = std::stoi(std::string(&_data[min], &_data[max]), nullptr, 2);
	int color_value = std::stoi(std::string(&_palette[index * 4], &_palette[index * 4 + 4]), nullptr, 2);

	return static_cast<color>(color_value);
}

int image::getWidth()
{
	return WIDTH;
}
int image::getHeight()
{
	return HEIGHT;
}
