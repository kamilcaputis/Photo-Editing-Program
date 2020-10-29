#include "Header.h"
#include <fstream>
using namespace std;

Header::Header()
{

}

Header::Header(string filename) //constructor base on filename
{
	ifstream file;
	file.open("input//" +filename, ios_base::binary);
	
	file.read(&idLength, sizeof(idLength));
	file.read(&colorMapType, sizeof(colorMapType));
	file.read(&dataTypeCode, sizeof(dataTypeCode));
	file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
	file.read((char*)&colorMapLength, sizeof(colorMapLength));
	file.read(&colorMapDepth, sizeof(colorMapDepth));
	file.read((char*)&xOrigin, sizeof(xOrigin));
	file.read((char*)&yOrigin, sizeof(yOrigin));
	file.read((char*)&width, sizeof(width));
	file.read((char*)&height, sizeof(height));
	file.read(&bitsPerPixel, sizeof(bitsPerPixel));
	file.read(&imageDescriptor, sizeof(imageDescriptor));

	file.close();
}
