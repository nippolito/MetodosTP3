#ifndef __IMAGE_H__
#define __IMAGE_H__


#include "ppmloader/ppmloader.cpp"
#include <string>

using namespace std;

class Image
{	
public:
	//Properties
	uchar* imageBuffer;
	string filePath;
	int height;
	int width;
	string label;


	//Methods
	Image(std::string newFilePath);
	Image(uchar* array);
	Image();
	~Image();

	void EditPixelValue(unsigned int pixelNumber, uchar value);
	void changePixelArray(uchar* array);
	void SaveImage(std::string newFilePath, _PPM_LOADER_PIXEL_TYPE pixelType);
	uchar obtainPixelValue(unsigned int pixelNumber);
	void aplanateImageArray(uchar* array);
	void convertToCSV(string name);
};

#endif //__IMAGE_H__
	