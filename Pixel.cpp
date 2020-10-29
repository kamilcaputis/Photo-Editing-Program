#include "Pixel.h"

Pixel::Pixel()
{
	blue = ' ';
	green = ' ';
	red = ' ';
}

Pixel::Pixel(string filename, Header &header)
{
	ifstream file;
	file.open("input//" + filename, ios_base::binary);
	file.seekg(18);
	short height = header.height;
	short width = header.width;
	unsigned int vectLength = height * width;
	Pixel pixel;

	for (unsigned int i = 0; i < vectLength; i++)
	{
		file.read((char*)&blue, sizeof(blue));
		file.read((char*)&green, sizeof(green));
		file.read((char*)&red, sizeof(red));

		pixel.blue = blue;
		pixel.green = green;
		pixel.red = red;

		pixels.push_back(pixel);
	}
	file.close();
}

