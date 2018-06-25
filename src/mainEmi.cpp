//#include "Image.cpp"
//#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
//#include "matrizRala.h"
#include "testsNipo.cpp"

using namespace std;

void Test1ParaMult(){ 	// pasa, todo OK
	Rala A = Rala(3,3);

	Rala B = Rala(3,2);

	/*
	0 0 3	* 1	2 		3 0
	2 1 0	  1	1  = 	3 5
	0 2 0	  1	0		2 2

	*/

	insertarElemento(A, 0, 2, 3);
	insertarElemento(A, 1, 0, 2);
	insertarElemento(A, 1, 1, 1);
	insertarElemento(A, 2, 1, 2);
	
	insertarElemento(B, 0, 0, 1);
	insertarElemento(B, 0, 1, 2);
	insertarElemento(B, 1, 0, 1);
	insertarElemento(B, 1, 1, 1);
	insertarElemento(B, 2, 0, 1);
	insertarElemento(B, 2, 1, 0);


	mostrarRala(&A);
	mostrarRala(&B);

	Rala C = Rala(A.n, B.m);
	multiplicacionMatricial(A, B, C);
	cout << endl;
	mostrarRala(&C);	
}

void TestParaAplanar(){ 	// pasa, todo OK
	Rala A = Rala(4,5);
	Rala B = Rala(1,20);
	/*
	0 0 0 0 0 	
	0 0 0 0 1 	 
	0 0 0 1 0 	
	0 0 1 0 0  

	*/

	insertarElemento(A, 1, 4, 1);
	insertarElemento(A, 2, 3, 1);
	insertarElemento(A, 3, 2, 1);
	
	mostrarRala(&A);

	cout << endl;
	cout << endl;
	cout << "APLANANDO" << endl;
	cout << endl;
	cout << endl;

	map<int,double> insert = convertirRayoEnFila(A); 
	reemplazarFila(B,0,insert);

	mostrarRala(&B);
	
}

void TestParaCM(){
	Rala A = Rala(4,4);

	insertarElemento(A, 0, 0, 1.003);
	insertarElemento(A, 0, 1, 2.9803);
	insertarElemento(A, 0, 2, 4);
	insertarElemento(A, 0, 3, 6.983);

	insertarElemento(A, 1, 0, 4.0001);
	insertarElemento(A, 1, 1, 6.4267);
	insertarElemento(A, 1, 2, 8.23);
	insertarElemento(A, 1, 3, 9);
	
	insertarElemento(A, 2, 0, 10);
	insertarElemento(A, 2, 1, 11);
	insertarElemento(A, 2, 2, 12.8731);
	insertarElemento(A, 2, 3, 10.01);
	
	insertarElemento(A, 3, 0, 78);
	insertarElemento(A, 3, 1, 43);
	insertarElemento(A, 3, 2, 0.0035);
	insertarElemento(A, 3, 3, 4.034);
	


	vector<double> b;
	b.push_back(2);
	b.push_back(7);
	b.push_back(4);
	b.push_back(8);

	vector<double> res = resolverCM(A, b);

	for (int i = 0; i < 3; ++i)
	{
		cout << res[i] << endl;
	}
}

/*
void testObtenerImagen(){
	string path = "../imgs_TC/tomo2.ppm";
	TCSimulator Simulator(path);
	int altura = Simulator.getHeight();
	int ancho = Simulator.getWidth();
	vector<double> res = Simulator.obtenerImagenPorRayos(generadorRayosCruzados(altura, ancho, 10), 0.5);

}
*/


void testApp(){
	string path = "exp_nipo/out/testCM.csv";
	TCSimulator Simulator(path,"emi_out/aver.csv");
	// Simulator.imageMatrix->convertToCSV("exp_nipo/tomo");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 120);
	//vector<pair<pair<double, double>, pair<double, double> > > asd;
	//Simulator.generarRayos(50, asd);
	vector<double> res = Simulator.obtenerImagenPorRayos(rayosTomo1, 0, 1);
	//Image* nuevaImagen = Simulator.regenerarImagen();
	//nuevaImagen->SaveImage("exp_nipo/in/ricardo.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);

}



int main(){
	//Test1ParaMult();
	//TestParaAplanar();
	testApp();
	//testObtenerImagen();
	return 1;
}