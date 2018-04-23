#ifndef IMAGE_H
#define IMAGE_H

class image
{
public:
	image(std::string data, std::string palette);
	
	std::string getData();
	std::string getPalette();

	color getPixelData(int x, int y);

	int getWidth();
	int getHeight();

private:
	std::string _data;
	std::string _palette;
};

#endif // !IMAGE_H
