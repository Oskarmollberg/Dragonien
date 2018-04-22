#ifndef IMAGE_H
#define IMAGE_H

class image
{
public:
	image(std::string data);
	
	std::string getData();

	int getPixelData(int x, int y);

	int getWidth();
	int getHeight();

private:
	std::string _data;
};

#endif // !IMAGE_H
