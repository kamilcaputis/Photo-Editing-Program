#include <iostream>
#include <fstream>
#include <chrono>
#include "Header.h"
#include "Pixel.h"
using namespace std;

void writeFile(vector<Pixel>& output, string filename, Header& header)
{
	ofstream file("output//" + filename, ios_base::binary);

	file.write(&header.idLength, sizeof(header.idLength));
	file.write(&header.colorMapType, sizeof(header.colorMapType));
	file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
	file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
	file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
	file.write((char*)&header.width, sizeof(header.width));
	file.write((char*)&header.height, sizeof(header.height));
	file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	//rgb info
	for (unsigned int i = 0; i < output.size(); i++)
	{
		file.write((char*)&output.at(i).blue, 1);
		file.write((char*)&output.at(i).green, 1);
		file.write((char*)&output.at(i).red, 1);
	}
}

vector<Pixel> multiply(vector<Pixel>& top, vector<Pixel>& bot)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < top.size(); i++)
	{
		float redTop = (float)top.at(i).red;
		float greenTop = (float)top.at(i).green;
		float blueTop = (float)top.at(i).blue;

		float redBot = (float)bot.at(i).red;
		float greenBot = (float)bot.at(i).green;
		float blueBot = (float)bot.at(i).blue;

		float r = ((redTop * redBot) / 255) + 0.5f;
		float g = ((greenTop * greenBot) / 255) + 0.5f;
		float b = ((blueTop * blueBot) / 255) + 0.5f;

		pix.red = (char)r;
		pix.green = (char)g;
		pix.blue = (char)b;

		output.push_back(pix);
	}
	return output;
}

vector<Pixel> subtract(vector<Pixel>& top, vector<Pixel>& bot)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < top.size(); i++)
	{
		int redTop = (int)top.at(i).red;
		int greenTop = (int)top.at(i).green;
		int blueTop = (int)top.at(i).blue;

		int redBot = (int)bot.at(i).red;
		int greenBot = (int)bot.at(i).green;
		int blueBot = (int)bot.at(i).blue;

		int r = (redBot - redTop);
		int g = (greenBot - greenTop);
		int b = (blueBot - blueTop);

		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;

		pix.red = (char)r;
		pix.green = (char)g;
		pix.blue = (char)b;

		output.push_back(pix);
	}
	return output;
}

vector<Pixel> screen(vector<Pixel>& top, vector<Pixel>& bot)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < top.size(); i++)
	{
		float redTop = (float)top.at(i).red / 255;
		float greenTop = (float)top.at(i).green / 255;
		float blueTop = (float)top.at(i).blue / 255;

		float redBot = (float)bot.at(i).red / 255;
		float greenBot = (float)bot.at(i).green/ 255;
		float blueBot = (float)bot.at(i).blue / 255;

		float r = (1 - ((1 - redBot) * (1 - redTop))) * 255;
		float g = (1 - ((1 - greenBot) * (1 - greenTop))) * 255;
		float b = (1 - ((1 - blueBot) * (1 - blueTop))) * 255;

		r += 0.5f;
		g += 0.5f;
		b += 0.5f;

		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;

		pix.red = (char)r;
		pix.green = (char)g;
		pix.blue = (char)b;

		output.push_back(pix);
	}
	return output;
}

vector<Pixel> overlay(vector<Pixel>& top, vector<Pixel>& bot)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < top.size(); i++)
	{
		float redTop = (float)top.at(i).red / 255;
		float greenTop = (float)top.at(i).green / 255;
		float blueTop = (float)top.at(i).blue / 255;

		float redBot = (float)bot.at(i).red / 255;
		float greenBot = (float)bot.at(i).green / 255;
		float blueBot = (float)bot.at(i).blue / 255;

		float r;
		float g;
		float b;
		
		if (redBot <= 0.5)
			r = (2 * redTop * redBot) * 255;
		if (greenBot <= 0.5)
			g= (2 * greenTop * greenBot) * 255;
		if (blueBot <= 0.5)
			b = (2 * blueTop * blueBot) * 255;
		if (redBot > 0.5)
			r = (1 - (2 * (1 - redTop) * (1 - redBot))) * 255;
		if (greenBot > 0.5)
			g = (1 - (2 * (1 - greenTop) * (1 - greenBot))) * 255;
		if (blueBot > 0.5)
			b = (1 - (2 * (1 - blueTop) * (1 - blueBot))) * 255;

		r += 0.5f;
		g += 0.5f;
		b += 0.5f;

		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;

		pix.red = (char)r;
		pix.green = (char)g;
		pix.blue = (char)b;

		output.push_back(pix);
	}

	return output;
}

vector<Pixel> addVal(vector<Pixel>& vect, int rd, int gn, int bl)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < vect.size(); i++)
	{
		int red = (int)vect.at(i).red;
		int green = (int)vect.at(i).green;
		int blue = (int)vect.at(i).blue;

		int r = red + rd;
		int g = green + gn;
		int b = blue + bl;

		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;

		pix.red = (char)r;
		pix.green = (char)g;
		pix.blue = (char)b;

		output.push_back(pix);
	}
	return output;
}

vector<Pixel> multiplyVal(vector<Pixel> vect, float rd, float gn, float bl)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < vect.size(); i++)
	{
		float red = (float)vect.at(i).red / 255;
		float green = (float)vect.at(i).green / 255;
		float blue = (float)vect.at(i).blue / 255;

		float r = (red * rd) * 255;
		float g = (green * gn) * 255;
		float b = (blue * bl) * 255;

		r += 0.5f;
		g += 0.5f;
		b += 0.5f;

		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;

		pix.red = (char)r;
		pix.green = (char)g;
		pix.blue = (char)b;

		output.push_back(pix);
	}
	return output;
}

vector<Pixel> setAll(vector<Pixel> & vect, string type)
{
	Pixel pix;
	vector<Pixel> output;

	if (type == "red")
	{
		for (unsigned int i = 0; i < vect.size(); i++)
		{
			unsigned char red = vect.at(i).red;

			pix.red = red;
			pix.green = red;
			pix.blue = red;

			output.push_back(pix);
		}
	}
	else if (type == "green")
	{
		for (unsigned int i = 0; i < vect.size(); i++)
		{
			unsigned char green = vect.at(i).green;

			pix.red = green;
			pix.green = green;
			pix.blue = green;

			output.push_back(pix);
		}
	}
	else if (type == "blue")
	{
		for (unsigned int i = 0; i < vect.size(); i++)
		{
			unsigned char blue = vect.at(i).blue;

			pix.red = blue;
			pix.green = blue;
			pix.blue = blue;

			output.push_back(pix);
		}
	}

	return output;
}

vector<Pixel> combineLayers(vector<Pixel>& r, vector<Pixel>& g, vector<Pixel>& b)
{
	Pixel pix;
	vector<Pixel> output;

	for (unsigned int i = 0; i < r.size(); i++)
	{

		pix.red = r.at(i).red;
		pix.green = g.at(i).green;
		pix.blue = b.at(i).blue;

		output.push_back(pix);
	}
	return output;
}

//------------TO USE ALL THE EXAMPLES MUST BE IN INPUT FOLDER-----------------//
/*bool check(vector<Pixel>& example, vector<Pixel>& output)
{
	for (int i = 0; i < example.size(); i++)
	{
		if (example.at(i).red == output.at(i).red)
			continue;
		else
			return false;
		if (example.at(i).green == output.at(i).green)
			continue;
		else
			return false;
		if (example.at(i).blue == output.at(i).blue)
			continue;
		else
			return false;
	}
	return true;
}*/

void test1(Pixel &layer1Pix, Pixel &pattern1Pix, Header &pattern1Header)
{
	vector<Pixel> output = multiply(layer1Pix.pixels, pattern1Pix.pixels);

	writeFile(output, "part1.tga", pattern1Header);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part1.tga");
	Pixel p = Pixel("EXAMPLE_part1.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 1 passed" << endl;
	else
		cout << "test 1 failed" << endl;*/

}

void test2(Pixel &layer2Pix, Pixel &carPix, Header &layer2Header)
{
	vector<Pixel> output = subtract(layer2Pix.pixels, carPix.pixels);

	writeFile(output, "part2.tga", layer2Header);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part2.tga");
	Pixel p = Pixel("EXAMPLE_part2.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 2 passed" << endl;
	else
		cout << "test 2 failed" << endl;*/
}

void test3(Pixel &layer1Pix, Pixel &pattern2Pix, Pixel &textPix, Header &textHeader)
{
	vector<Pixel> bot = multiply(layer1Pix.pixels, pattern2Pix.pixels);
	vector<Pixel> output = screen(textPix.pixels, bot);

	writeFile(output, "part3.tga", textHeader);

	/////////////////TEST/////////////// 
	/*Header h = Header("EXAMPLE_part3.tga");
	Pixel p = Pixel("EXAMPLE_part3.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 3 passed" << endl;
	else
		cout << "test 3 failed" << endl;*/
}

void test4(Pixel &layer2Pix, Pixel &pattern2Pix, Pixel &circlesPix, Header pattern2Header)
{
	vector<Pixel> bot = multiply(layer2Pix.pixels, circlesPix.pixels);
	vector<Pixel> output = subtract(pattern2Pix.pixels, bot);

	writeFile(output, "part4.tga", pattern2Header);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part4.tga");
	Pixel p = Pixel("EXAMPLE_part4.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 4 passed" << endl;
	else
		cout << "test 4 failed" << endl;*/
}

void test5(Pixel &layer1Pix, Pixel &pattern1Pix, Header &layer1Header)
{
	vector<Pixel> output = overlay(layer1Pix.pixels, pattern1Pix.pixels);

	writeFile(output, "part5.tga", layer1Header);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part5.tga");
	Pixel p = Pixel("EXAMPLE_part5.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 5 passed" << endl;
	else
		cout << "test 5 failed" << endl;*/
}

void test6(Pixel &carPix, Header &carHeader)
{
	vector<Pixel> output = addVal(carPix.pixels, 0, 200, 0);

	writeFile(output, "part6.tga", carHeader);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part6.tga");
	Pixel p = Pixel("EXAMPLE_part6.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 6 passed" << endl;
	else
		cout << "test 6 failed" << endl;*/
}

void test7(Pixel &carPix, Header &carHeader)
{
	vector<Pixel> output = multiplyVal(carPix.pixels, 4, 1, 0);

	writeFile(output, "part7.tga", carHeader);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part7.tga");
	Pixel p = Pixel("EXAMPLE_part7.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 7 passed" << endl;
	else
		cout << "test 7 failed" << endl;*/
}

void test8(Pixel &carPix, Header &carHeader)
{
	vector<Pixel> red = setAll(carPix.pixels, "red");
	vector<Pixel> green = setAll(carPix.pixels, "green");
	vector<Pixel> blue = setAll(carPix.pixels, "blue");

	writeFile(red, "part8_r.tga", carHeader);
	writeFile(green, "part8_g.tga", carHeader);
	writeFile(blue, "part8_b.tga", carHeader);

	/////////////////TEST///////////////
	/*Header hb = Header("EXAMPLE_part8_b.tga");
	Pixel pb = Pixel("EXAMPLE_part8_b.tga", hb);
	Header hg = Header("EXAMPLE_part8_g.tga");
	Pixel pg = Pixel("EXAMPLE_part8_g.tga", hg);
	Header hr = Header("EXAMPLE_part8_r.tga");
	Pixel pr = Pixel("EXAMPLE_part8_r.tga", hr);

	bool passed = check(pb.pixels, blue);
	bool passed2 = check(pg.pixels, green);
	bool passed3 = check(pr.pixels, red);
	if (passed && passed2 && passed3)
		cout << "test 8 passed" << endl;
	else
		cout << "test 8 failed" << endl;*/
}

void test9(Pixel &layerRPix, Pixel &layerGPix, Pixel &layerBPix, Header &layerRHeader)
{
	vector<Pixel> output = combineLayers(layerRPix.pixels, layerGPix.pixels, layerBPix.pixels);

	writeFile(output, "part9.tga", layerRHeader);

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part9.tga");
	Pixel p = Pixel("EXAMPLE_part9.tga", h);
	bool passed = check(p.pixels, output);
	if (passed)
		cout << "test 9 passed" << endl;
	else
		cout << "test 9 failed" << endl;*/
}

void test10(Pixel &text2Pix, Header &header)
{
	float size = text2Pix.pixels.size();

	ofstream file("output//part10.tga", ios_base::binary);

	file.write(&header.idLength, sizeof(header.idLength));
	file.write(&header.colorMapType, sizeof(header.colorMapType));
	file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
	file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
	file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
	file.write((char*)&header.width, sizeof(header.width));
	file.write((char*)&header.height, sizeof(header.height));
	file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	//rgb info
	for (float i = size - 1; i >= 0; i--)
	{
		file.write((char*)&text2Pix.pixels.at(i).blue, 1);
		file.write((char*)&text2Pix.pixels.at(i).green, 1);
		file.write((char*)&text2Pix.pixels.at(i).red, 1);
	}

	/////////////////TEST///////////////
	/*Header h = Header("EXAMPLE_part10.tga");
	Pixel p = Pixel("EXAMPLE_part10.tga", h);
	Header h10 = Header("part10.tga");
	Pixel p10 = Pixel("part10.tga", h10);
	bool passed = check(p.pixels, p10.pixels);
	if (passed)
		cout << "test 10 passed" << endl;
	else
		cout << "test 10 failed" << endl;*/

}

int main()
{
	
	Header layer1Header = Header("layer1.tga");
	Header pattern1Header = Header("pattern1.tga");
	Header layer2Header = Header("layer2.tga");
	Header carHeader = Header("car.tga");
	Header textHeader = Header("text.tga");
	Header pattern2Header = Header("pattern2.tga");
	Header circlesHeader = Header("circles.tga");
	Header layerRHeader = Header("layer_red.tga");
	Header layerGHeader = Header("layer_green.tga");
	Header layerBHeader = Header("layer_blue.tga");
	Header text2Header = Header("text2.tga");

	Pixel layer1Pix = Pixel("layer1.tga", layer1Header);
	Pixel pattern1Pix = Pixel("pattern1.tga", pattern1Header);
	Pixel layer2Pix = Pixel("layer2.tga", layer2Header);
	Pixel carPix = Pixel("car.tga", carHeader);
	Pixel pattern2Pix = Pixel("pattern2.tga", pattern2Header);
	Pixel textPix = Pixel("text.tga", textHeader);
	Pixel circlesPix = Pixel("circles.tga", circlesHeader);
	Pixel layerRPix = Pixel("layer_red.tga", layerRHeader);
	Pixel layerGPix = Pixel("layer_green.tga", layerGHeader);
	Pixel layerBPix = Pixel("layer_blue.tga", layerBHeader);
	Pixel text2Pix = Pixel("text2.tga", text2Header);

	test1(layer1Pix, pattern1Pix, pattern1Header);
	test2(layer2Pix, carPix, layer2Header);
	test3(layer1Pix, pattern2Pix, textPix, textHeader);
	test4(layer2Pix, pattern2Pix, circlesPix, pattern2Header);;
	test5(layer1Pix, pattern1Pix, layer1Header);
	test6(carPix, carHeader);
	test7(carPix, carHeader);
	test8(carPix, carHeader);
	test9(layerRPix, layerGPix, layerBPix, layerRHeader);
	test10(text2Pix, text2Header);
	
	return 0;
}

