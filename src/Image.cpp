
#include <iostream>
#include <cstddef>
#include <fstream>
#include "Image.h"
#include <cmath>
#include <vector>


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
string obtainImgExtension(string path){
	int n = path.size() - 1 ;
	int indiceUltimoPunto = n;
	for( ; indiceUltimoPunto >= 0 ; indiceUltimoPunto --){
		if(path[indiceUltimoPunto] == '.'){
			break;
		}
	}
	return path.substr(indiceUltimoPunto, path.size()-indiceUltimoPunto);
}
Image::Image(uchar* array){
	imageBuffer = array;
}
Image::Image(std::string newFilePath){

	string extension = obtainImgExtension(newFilePath);
	if (extension == ".ppm"){
		width = 0, height = 0;
  		PPM_LOADER_PIXEL_TYPE pt = PPM_LOADER_PIXEL_TYPE_INVALID;
	//  std::string filename = "buda.0.ppm";
  		filePath = newFilePath;
  		label = obtainPathUntilLastFolder(filePath);
  		bool ret = LoadPPMFile(&imageBuffer, &width, &height, &pt, filePath.c_str());
  		cout << "el size del image buffer es : " ; 
  		cout << sizeof(*imageBuffer) << endl;
  		cout << "height es : " << height<< endl;
  		cout << "width es : "<< width << endl;
  		
	}
	//Apartir de este momento esta clase no es mas exportable ya que no existe hardcodeo mas hermoso y horrible que asumir .csv = .dcm
	else if (extension == ".csv"){
		ifstream inFile;
		inFile.open(newFilePath);
		
		string pixel;
		vector<uchar> pixels = vector<uchar>();
		int alto = 1;
		while(getline(inFile,pixel,',')){
			int breakDeLinea = 0;
			for (int i = 0; i < pixel.size(); ++i)
			{
				if(pixel[i] == '\n' && i != pixel.size() - 1)
				{
					alto++;
					breakDeLinea = i;
				}
			}
			if (breakDeLinea == 0){
				int pixelRead =  floor(stoi(pixel)/256);
				pixels.push_back( (uchar) pixelRead);
			}
			else{
				int pixelRead1 =  floor(stoi(pixel.substr(0,breakDeLinea))/256);
				int pixelRead2 =  floor(stoi(pixel.substr(breakDeLinea+1,pixel.size()-breakDeLinea+1))/256);
				pixels.push_back((uchar) pixelRead1);
				pixels.push_back((uchar) pixelRead2);
			}	
		}
		height = alto;
		width = pixels.size() / height;
		imageBuffer = new uchar[pixels.size()];
		for (int i = 0; i < pixels.size(); ++i)
		{
			imageBuffer[i] = pixels[i];
		}
	
	}
	else {
		cout << "Creando una imagen con extension no permitida" << endl;
	}
  	
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

Image::Image(){
	
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

void Image::SaveImage(std::string newFilePath, _PPM_LOADER_PIXEL_TYPE  pixelType){

 	char comments[100];
 	bool ret = SavePPMFile(newFilePath.c_str(),imageBuffer,width,height,pixelType, comments);
}



