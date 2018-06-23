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




void pruebaCasoReal(){
	string path = "../imgs_TC_out/exp_nipo/in/juan.csv";
	TCSimulator Simulator(path, "grego_out/tuvieja.csv");
	//Simulator.logInfoImage();
	Simulator.generarRayos(2000, vector<pair<pair<double,double>, pair<double,double> > >());
	Image imgRes = Simulator.regenerarImagenConDiscretizacion(1);


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












