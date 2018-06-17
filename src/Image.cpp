
#include <iostream>
#include <cstddef>
#include "Image.h"

using namespace std;

string obtainPathUntilLastFolder(string path){
	int n = path.size() - 1 ;
	int indiceUltimBarra = n;
	for( ; indiceUltimBarra >= 0 ; indiceUltimBarra --){
		if(path[indiceUltimBarra] == '/'){
			break;
		}
	}
	return path.substr(0,indiceUltimBarra);
}
Image::Image(uchar* array){
	imageBuffer = array;
}
Image::Image(std::string newFilePath){

	width = 0, height = 0;
  	PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;
	//  std::string filename = "buda.0.ppm";
  	filePath = newFilePath;
  	label = obtainPathUntilLastFolder(filePath);
  	bool ret = LoadPPMFile(&imageBuffer, &width, &height, &pt, filePath.c_str());
  	
  	// int counter = 0;
  	// while(true){
  	// 	std::cout << counter << std::endl;
  	// 	imageBuffer[counter];
  	// 	counter++;
  	// }
	
};
Image::~Image(){
	delete [] imageBuffer;
};


void Image::changePixelArray(uchar* array){
	if ( imageBuffer == NULL)
		cout << "solo llama a esta funcion si ya tiene una imagen cargada" << endl;
	delete imageBuffer;
	imageBuffer = array;
}

void Image::aplanateImageArray(uchar* array){
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			array[i * width + j] = obtainPixelValue(i * width + j);
		}
	}
}

void Image::EditPixelValue(unsigned int pixelNumber, uchar value){
	cout << "no recomiendo llamar a esta funcion, bugs de peter" << endl;
	imageBuffer[pixelNumber] = value;
}

uchar Image::obtainPixelValue(unsigned int pixelNumber){
	return imageBuffer[pixelNumber];
}

void Image::SaveImage(std::string newFilePath){

 	char comments[100];

  	bool ret = SavePPMFile(newFilePath.c_str(),imageBuffer,width,height,PPM_LOADER_PIXEL_TYPE_RGB_8B, comments);
}



