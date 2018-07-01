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
#include "auxiliar.h"


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
/*
void test(){
	string pathTomo = "../imgs_TC_out/tomo.csv";
	string pathImgs = "grego_exp_img_day2";
	string pathRayos = "grego_exp_rayos_day2";
	int cantDeRayosInit = 1024;
	int cantRayosAct = cantDeRayosInit;

	int k = 5;
	for(int i = 10 ; i < 40; i++){
		cantRayosAct = cantDeRayosInit * i ;
		for(int i = 0 ; i < k; i++){
			cout << "cant de Rayos : " << cantRayosAct << endl;
			cout << "iteracion : " << i << endl; 
			TCSimulator Simulator(pathTomo, pathImgs + "/" + to_string(cantRayosAct)+ "_" + to_string(i),
			 pathRayos  + "/" + to_string(cantRayosAct) + "_" + to_string(i));
			Simulator.obtenerImagenPorRayos(0.1, 4,1,cantRayosAct);
		} 
	}
}


void test2(){
	string pathTomo = "../imgs_TC_out/tomo.csv";
	string pathImgs = "grego_exp_img_ord_2_day2";
	string pathRayos = "grego_exp_rayos_ord_2_day2";
	int cantDeRayosInit = 1024;
	int cantRayosAct = cantDeRayosInit;

	int k = 1;
	for(int i = 13 ; i < 40; i++){
		cantRayosAct = cantDeRayosInit * i ;
		for(int i = 0 ; i < k; i++){
			cout << "cant de Rayos : " << cantRayosAct << endl;
			cout << "iteracion : " << i << endl; 
			TCSimulator Simulator(pathTomo, pathImgs + "/" + to_string(cantRayosAct)+ "_" + to_string(i),
			 pathRayos  + "/" + to_string(cantRayosAct) + "_" + to_string(i));
			Simulator.obtenerImagenPorRayos(0.1, 2,1,cantRayosAct);
		} 
	}
}

//path imagen / path saving / rayos_saving_path / orden de magnitud / cantidad de rayos

int main2(int argc, char *argv[]){
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


void pruebaRayos(){
	string path = "../imgs_TC_out/resize_tomo.csv";
	TCSimulator Simulator(path, "grego_out/pruebaRayos.csv", "grego_out/rayos_pruebaRayos.csv");
	//Simulator.logInfoImage();
	vector<pair<pair<double,double>, pair<double,double> > > muchasEstrellas = generarMuchasEstrellas();
	cout << "cantidad de rayos: " << muchasEstrellas.size() << endl;
	Simulator.generarRayos(muchasEstrellas.size(), muchasEstrellas);
	Image imgRes = Simulator.regenerarImagenConDiscretizacion(4);

	return;
}
/*
double ECM(vector<double> v1, vector<double> v2){
		double res = 0;
		for(int i = 0; i < v1.size(); i++){
			res += pow((v1[i] - v2[i]), 2);
		}
		res = res / v1.size();
		return res;
	}
*/
void calcularEcm(int argc, char *argv[]){
	vector<vector<int> > original = levantarCsv(argv[1]);
	vector<vector<int> > construida = levantarCsv(argv[2]);

	vector<double> original_d = pasarDeImagenAVecDouble(original);
	vector<double> construida_d = pasarDeImagenAVecDouble(construida);

	original_d = normalizar(original_d);
	construida_d = normalizar(construida_d);
	cout << "el ecm entre las dos imagenes es : " << ECM(original_d, construida_d) << endl;
}


double calcularEcmEMI(string pathoriginal, string pathconstruida){
	cout <<"calculando ECM" << endl;
	vector<vector<int> > original = levantarCsv(pathoriginal);
	vector<vector<int> > construida = levantarCsv(pathconstruida);

	cout << "paso 1" << endl;
	vector<double> original_d = pasarDeImagenAVecDouble(original);
	vector<double> construida_d = pasarDeImagenAVecDouble(construida);
	cout << "paso 2" << endl;
	original_d = normalizar(original_d);
	construida_d = normalizar(construida_d);
	return ECM(original_d, construida_d); 

}

/*
int main(int argc, char *argv[]){
	calcularEcm(argc, argv);
	//main2(argc, argv);
	//mostrarRayos();
	//pruebaRayos();
	//test2();
	return 0 ; 
}
*/






