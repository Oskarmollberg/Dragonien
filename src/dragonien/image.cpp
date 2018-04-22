/*
	image.cpp is used to hold a texture. 

	An image is stored via 'indirect color' with an additional palette for color.
*/


#include <algorithm>
#include <bitset>

#include "image.h"

const int BITS_PER_PIXEL = 4;

const int WIDTH	= 8;
const int HEIGHT = 8;

image::image(std::string data)
{
	_data = data;
}

std::string image::getData()
{
	return _data;
}

int image::getPixelData(int x, int y)
{
	size_t min = ((y - 1) * getWidth() + (x - 1)) * BITS_PER_PIXEL;
	size_t max = min + BITS_PER_PIXEL;

	std::string s(&_data[min], &_data[max]);

	return std::stoi(s, nullptr, 2);
}

int image::getWidth()
{
	return WIDTH;
}
int image::getHeight()
{
	return HEIGHT;
}
