#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"
#include <algorithm> 


using namespace std;




void pruebaCasoReal_1(){
	string path = "../imgs_TC_out/resize_tomo.csv";
	TCSimulator Simulator(path, "grego_out/tomo_128x128_ord4.csv");
	//Simulator.logInfoImage();
	Simulator.generarRayos(10000, vector<pair<pair<double,double>, pair<double,double> > >());
	Image imgRes = Simulator.regenerarImagenConDiscretizacion(4);

	return;
}

void pruebaCasoReal_2(){
	string path = "../imgs_TC_out/tomo.csv";
	TCSimulator Simulator(path, "grego_out/tomo_128x128_ord4_lev16_cap16.csv");
	//Simulator.logInfoImage();
	Simulator.generarRayos(10000, vector<pair<pair<double,double>, pair<double,double> > >());
	Image imgRes = Simulator.regenerarImagenConDiscretizacion(4);

	return;
}

void pruebaCasoReal_3(){
	string path = "../imgs_TC_out/tomo.csv";
	TCSimulator Simulator(path, "grego_out/tomo_128x128_ord4_lev8_cap8.csv");
	//Simulator.logInfoImage();
	Simulator.generarRayos(10000, vector<pair<pair<double,double>, pair<double,double> > >());
	Image imgRes = Simulator.regenerarImagenConDiscretizacion(4);

	return;
}

//path imagen / path saving / orden de magnitud / cantidad de rayos
int main(int argc, char *argv[]){
	string path = argv[1];
	string saving_path = argv[2];
	string rayos_saving_path = argv[3];
	int magnitud = stoi(argv[4]);
	int cant_rayos = stoi(argv[5]);
	TCSimulator Simulator(path, saving_path,rayos_saving_path);
	//Simulator.logInfoImage();
	Simulator.generarRayos(cant_rayos, vector<pair<pair<double,double>, pair<double,double> > >());
	Image imgRes = Simulator.regenerarImagenConDiscretizacion(magnitud);

	
	return 0;
}












