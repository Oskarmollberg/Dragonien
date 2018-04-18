/*
	image.cpp is used to hold a texture. 

	An image is stored via 'indirect color' with an additional palette for color.
*/


#include <bitset>

#include "image.h"

const int BITS_PER_PIXEL = 4;

const int WIDTH		= 8;
const int HEIGHT	= 8;

image::image(std::string data)
{
	_data = std::bitset<256>(data);
}
image::image(std::bitset<256> data)
{
	_data = data;
}

std::bitset<256> image::getData()
{
	return _data;
}

int image::getPixelData(int x, int y)
{
	size_t min = ((y - 1) * getWidth() + (x - 1)) * BITS_PER_PIXEL;
	size_t max = ((y - 1) * getWidth() + (x - 1)) * BITS_PER_PIXEL + BITS_PER_PIXEL;

	unsigned long mask = 1;
	unsigned long result = 0;
	for (size_t i = min; i < max; ++i)
	{
		if (_data.test(i))
			result |= mask;
		mask <<= 1;
	}
	return result;
}

int image::getWidth()
{
	return WIDTH;
}
int image::getHeight()
{
	return HEIGHT;
}
