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


int main(){
	//testNoiser();

	//pruebaCasoRealDiscretizando();
	//testReal();
	pruebaCasoReal_1();
	//testJuguete();
	//pruebaImagenes();
	//pruebaCasoReal();
	//pruebaLevantarDCMenCSV();
	return 0;
}












