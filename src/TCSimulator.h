#ifndef __SIMULADOR_H__
#define __SIMULADOR_H__

#include <iostream>
#include <vector>
#include <math.h>
#include "matrizRala.h"
#include <stdlib.h>
#include <algorithm> 

using namespace std;

int green=0;
int red = 1;
int blue = 2;

struct Recta{
	double a;
	double b;
	
	Recta(){}

	Recta(double a2, double b2){
		a = a2;
		b = b2;
	}

	double f(int x){
		return a*x + b;
	}

	void print(){
		cout << "y = " << a << ".x + (" << b <<")" << endl;
	}
};

class TCSimulator
{
public:
	
	//Properties
	Image* imageMatrix;

	//Methods

	//Agregar ruido con distribucion salt & pepper, paso p probabilidad como argumento y defino t = 1-p,
	//iterando sobre los pixeles obtengo un numero random r y si p<r<t entonces el pixel se mantiene igual,
	//si no, r<p => pixel=negro, r>t => pixel=blanco 
	void addSnPNoiseToSimulation(Image* newImage, double p){
		srand (time(NULL));
				
		double thresh = 1 - p;
		cout << imageMatrix->height << " " << imageMatrix->width << endl;
		for (int i = 0; i < (imageMatrix->height)*3; ++i)
		{
			for (int j = 0; j < (imageMatrix->width)*3; ++j)
			{
				double r = (double) rand() / (RAND_MAX);
				//cout << r << endl;
				if (r<p){
					newImage->EditPixelValue(i* imageMatrix->width + j, 55);
				}
				else if (thresh<r){
					newImage->EditPixelValue(i* imageMatrix->width + j, 200);
				}
				else{
					cout << i << ", " << j << endl;
					newImage->EditPixelValue(i* imageMatrix->width + j, imageMatrix->obtainPixelValue(i* imageMatrix->width + j));
				}
				
			}
		}


	}

	//pixel 1 siempre a izquierda del pixel 2
	void createTCRay(pair<double,double> pixel1, pair<double,double> pixel2, Rala& distances){
		//nos aseguramos que el primer pixel tenga un x menor a pixel2
		//los rayos pueden "ir en sentido contrario" pero para la simulacion los trataremos SIEMPRE
		//de izquierda a derecha
		//PRECONDICION OBLIGATORIA: ambos puntos deben estar en los bordes, osea x = 0 o x = ancho o y = 0 o y = alto

		double a = (double) (pixel2.second - pixel1.second) / (double)(pixel2.first - pixel1.first);
		double b = pixel1.second - a * pixel1.first;

		Recta recta = Recta(a,b);
		recta.print();
		
		if(a > 0){ // si la pendiente es poisitiva
			for (int i = 0; i <= distances.m; ++i){
				int j = (int) floor(recta.f(i));
				if(j < 0) j = 0 ; // esto para cuando la recta empieza desde el piso
				double k = recta.f(i+1); // esta bien que este no sea un entero aviso
				if(k < 0) k = 0; // esto cuando no pasa por ninguna de las dos columnas
				if(k > distances.n ) k = distances.n  ;// esto cuando se va por el techo la recta. 

				for (; j < k; ++j){
					cout << i << " " << j << endl;
					insertarElemento(distances,j, i,  1);
				}
			}		
		}
		else if( a < 0){ // si la pendiente es negativa
			for (int i = 0; i < distances.m; ++i){
				int j = (int) ceil(recta.f(i));
				if(j > distances.n) j = distances.n ; // esto para cuando la recta empieza desde el techo
				double k = recta.f(i+1); 
				if(k > distances.n) k = distances.n; // esto cuando no pasa por ninguna de las dos columnas
				if(k < 0) k = 0; // esto cuando se va por el piso la recta
				//cout << "i: " << i << ", j: " << j << ", k: " << k << endl; 
				for (; j > k; j--)
				{
					cout << i << " " << j-1 << endl;
					insertarElemento(distances, j-1, i , 1);
				}
			}	
		}
		else{
			cout << "te toco una funcion constante" << endl;
		}
	}

	TCSimulator(string imageSimulatedPath){
		imageMatrix = new Image(imageSimulatedPath);
	}

	TCSimulator(){
		cout << "Mira que estas creando un simulador sin imagen.." << endl;
	}

	~TCSimulator(){
		delete imageMatrix;		
	}

	int getWidth(){
		return imageMatrix->width;
	}


	int getHeight(){
		return imageMatrix->height;
	}

	double tiempoDeRecorrido(Rala& distances){
		double tiempo = 0 ;
		int n = distances.n;
		int m = distances.m;
		for(int i = 0 ; i < n ; i ++){
			for(int j = 0 ; j < m; j ++){
				tiempo += distances.conex[i][j] * (imageMatrix->imageBuffer[i*m*3 + j + green] + imageMatrix->imageBuffer[i*m*3 + j + red] + imageMatrix->imageBuffer[i*m*3 + j + blue]) / 3;
			}
		}
		return tiempo;
	}


	//setea en pixel1 y pixel2 dos puntos random dentro de la planilla
	//ACLARACION: siempre pixel1 esta a la izquierda de pixel2
	void createTwoRandomPoints(int n, int m, pair<double,double>& pixel1, pair<double,double>& pixel2){
		srand (time(NULL));
		double x1 = rand() % m;
		double x2 = rand() % m;

		double y1 = rand() % n;
		double y2 = rand() % n;

		if (x1 > x2) {
			swap(x1,x2);
		}

		pixel1.first = x1;
		pixel1.second = y1;

		pixel2.first = x2;
		pixel2.second = y2;

		cout << "pixel1: " << x1 << ", " << y1 << endl;
		cout << "pixel2: " << x2 << ", " << y2 << endl;
	}
		
private:
	bool isNotInEdge(pair<int,int> pixel){
		return pixel.first != 0 && pixel.first != getWidth()-1 && pixel.second != 0 && pixel.second != getHeight()-1;
	}

	bool areInSameEdge(pair<int,int> pixel1, pair<int,int> pixel2){
		return (pixel1.first == pixel2.first && (pixel1.first == 0 || pixel1.first == getWidth()-1 )) || (pixel1.second == pixel2.second && (pixel1.second = 0 || pixel1.second == getHeight()-1) );
	}
	
};

#endif