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

void testJuguete(){
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

int main(){
	//testReal();
	testJuguete();

	return 0;
}