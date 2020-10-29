#pragma once
#include <iostream>
using namespace std;

struct Header
{
	char idLength = ' ';
	char colorMapType = ' ';
	char dataTypeCode = ' ';
	short colorMapOrigin = 0;
	short colorMapLength = 0;
	char colorMapDepth = ' ';
	short xOrigin = 0;
	short yOrigin = 0;
	short width = 0;
	short height = 0;
	char bitsPerPixel = ' ';
	char imageDescriptor = ' ';

	Header();
	Header(string filename);
};
