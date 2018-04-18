#ifndef IMAGE_H
#define IMAGE_H

class image
{
public:
	image(std::string data);
	image(std::bitset<256> data);
	
	std::bitset<256> getData();

	int getPixelData(int x, int y);

	int getWidth();
	int getHeight();

private:
	std::bitset<256> _data;
};

#endif // !IMAGE_H
