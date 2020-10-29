#pragma once
#include "Header.h"
#include <fstream>
#include <vector>
using namespace std;

struct Pixel
{   
	unsigned char blue = ' ';
	unsigned char green = ' ';
	unsigned char red = ' ';

	vector<Pixel> pixels;

	Pixel();
	Pixel(string filename, Header &header);
};

