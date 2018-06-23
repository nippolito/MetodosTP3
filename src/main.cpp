#include "Image.cpp"
#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"


using namespace std;


void testReal(){
	string path = "../imgs_TC/tomo.ppm";
	
	TCSimulator Simulator(path);
	Rala matrizDistancias = Rala(Simulator.getHeight(), Simulator.getWidth());
	pair<double,double> pixel1;
	pair<double,double> pixel2;
	Simulator.createTwoRandomPoints(Simulator.getHeight(), Simulator.getWidth(), pixel1, pixel2);
	Simulator.createTCRay(pixel1, pixel2, matrizDistancias);
}

void testNoiser(){
	string path = "../imgs_TC/tomo.ppm";
	
	TCSimulator Simulator(path);
	Image* noiseImage = new Image(path);
	Simulator.addSnPNoiseToSimulation(noiseImage, 0.1);
	noiseImage->SaveImage("../imgs_TC/tomoConRuido.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);
	delete noiseImage;
}

void testPendienteNegativa(){
	TCSimulator Simulator;
	int n = 4;
	int m = 4;
	Rala matrizDistancias = Rala(n, m);
	pair<double,double> pixel1 = pair<double,double>(0.5,4);
	pair<double,double> pixel2 = pair<double,double>(1.8,0);
	//Simulator.createTwoRandomPoints(n, m, pixel1, pixel2);
	//cout << "BK 4" << endl;

}


void testPendientePositiva(){
	TCSimulator Simulator;
	int n = 4;
	int m = 4;
	Rala matrizDistancias = Rala(n, m);
	pair<double,double> pixel1 = pair<double,double>(0.5,4);
	pair<double,double> pixel2 = pair<double,double>(1.8,0);
	//Simulator.createTwoRandomPoints(n, m, pixel1, pixel2);
	//cout << "BK 4" << endl;
	Simulator.createTCRay(pixel1, pixel2, matrizDistancias);
}


void pruebaModificarImagen(TCSimulator& Simulator){
	int n = Simulator.imageMatrix->height;
	int m = Simulator.imageMatrix->width;
	for(int i = 0 ; i < n ; i ++){
		for(int j = 0 ; j < m*3; j+= 3){
			//cout << "(g: " << (int)Simulator.imageMatrix->imageBuffer[i*m + j + 0 ] << ", r: " << (int)Simulator.imageMatrix->imageBuffer[i*m + j + 1] << ", b: " << (int)Simulator.imageMatrix->imageBuffer[i*m + j + 2] << ")" << endl;  
			Simulator.imageMatrix->imageBuffer[i*m*3 + j] = (uchar)0;
			Simulator.imageMatrix->imageBuffer[i*m*3 + j+1] = (uchar)255;
			Simulator.imageMatrix->imageBuffer[i*m*3 + j+2] = (uchar)0;
		}
	}
}

void pruebaVerCuantoImitarImagenSePuede(TCSimulator& Simulator){
	int n = Simulator.imageMatrix->height;
	int m = Simulator.imageMatrix->width;
	for(int i = 0 ; i < n ; i ++){
		for(int j = 0 ; j < m*3; j+= 3){
			double promedio = (Simulator.imageMatrix->imageBuffer[i*m*3 + j] + Simulator.imageMatrix->imageBuffer[i*m*3 + j + 1]  +Simulator.imageMatrix->imageBuffer[i*m*3 + j + 2]) / 3;
			Simulator.imageMatrix->imageBuffer[i*m*3 + j] = promedio;
			Simulator.imageMatrix->imageBuffer[i*m*3 + j+1] = promedio;
			Simulator.imageMatrix->imageBuffer[i*m*3 + j+2] = promedio;
		}
	}
}




void pruebaImagenes(){
	string path = "../imgs_TC/tomo2.ppm";
	TCSimulator Simulator(path);
	pruebaVerCuantoImitarImagenSePuede(Simulator);
	Simulator.imageMatrix->SaveImage("../imgs_TC/prueba.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);
}

void pruebaLevantarDCMenCSV(){
	string path = "../imgs_TC_out/1.2.826.0.1.3680043.2.656.1.138.35.csv";
	TCSimulator Simulator(path);
	Simulator.imageMatrix->SaveImage("../imgs_TC/pruebaDcm.ppm", PPM_LOADER_PIXEL_TYPE_GRAY_8B);
}

void pruebaCasoRealDiscretizando(){
	string path = "../imgs_TC/tomo.ppm";
	TCSimulator Simulator(path);

	int cantRayos = 20000;
	Simulator.generarRayos(cantRayos, vector<pair<pair<double,double>, pair<double,double> > > ());
	Image* imagenReconstruida = Simulator.regenerarImagenConDiscretizacion(4);
	imagenReconstruida->SaveImage("../imgs_TC/imagenReconstruida.ppm", PPM_LOADER_PIXEL_TYPE_GRAY_8B);
}


void pruebaCasoReal(){
	string path = "../imgs_TC/tomo.ppm";
	TCSimulator Simulator(path);
	//Simulator.logInfoImage();
	Simulator.generarRayos(2000, vector<pair<pair<double,double>, pair<double,double> > >());
	Image* imgRes = Simulator.regenerarImagen();

	
	imgRes->SaveImage("../imgs_TC/prueba.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);

	return;
}

int main(){
	//testNoiser();

	//pruebaCasoRealDiscretizando();
	//testReal();
	pruebaCasoReal();
	//testJuguete();
	//pruebaImagenes();
	//pruebaCasoReal();
	//pruebaLevantarDCMenCSV();
	return 0;
}












