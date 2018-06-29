//#include "Image.cpp"
#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"
//#include "testsNipo.cpp"

using namespace std;
// función para randoms en double
double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


vector<pair<pair<double,double>, pair<double,double> > > generadorRayosCompletoHorizontal(int m, int n){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<pair<double, double>, pair<double, double> > pixel1;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	for (int i = 0; i < m; ++i)
	{	
		punto1.first = 0;
		punto1.second = i;
		punto2.first = n;
		punto2.second = i+1;
		
		pixel1.first = punto1;
		pixel1.second = punto2;
		res.push_back(pixel1);
		//cout << "agrege los puntos: (" <<pixel1.first.first << "," << pixel1.first.second << ") y ("<< pixel1.second.first <<","<< pixel1.second.second<<")"<< endl;	
	}
	
	return res;
}


vector<pair<pair<double,double>, pair<double,double> > > generadorRayosCompletoColumnas(int m, int n){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<pair<double, double>, pair<double, double> > pixel1;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	for (int i = 0; i < m; ++i)
	{	
		punto1.first = i;
		punto1.second = m;
		punto2.first = i++;
		punto2.second = 0;
		
		pixel1.first = punto1;
		pixel1.second = punto2;
		res.push_back(pixel1);
		//cout << "agrege los puntos: (" <<pixel1.first.first << "," << pixel1.first.second << ") y ("<< pixel1.second.first <<","<< pixel1.second.second<<")"<< endl;	
	}
	
	return res;
}


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



vector<pair<pair<double,double>, pair<double,double> > > generadorRayosPuntoFijoIzq(int m, int n, int k){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<pair<double, double>, pair<double, double> > pixel1;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	// primer punto en el extremo izquierdo.
	// genero un punto en cualquier lado del extremo izquierdo
	punto1.first = 0;
	punto1.second = fRand(0, (double) m);
	if(punto1.second == 0) punto1.second += 0.1;
	pixel1.first = punto1;

	// arranco por generar los k rayos hacia arriba
	punto2.second = m;
	double valor = (double) n / k;
	for(int j = 0; j < k; j++){
		punto2.first = valor;
		valor += (double) n / k;

		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	// ahora los k rayos hacia la derecha. Freno uno antes porque sino repito un punto
	punto2.first = n;
	valor = (double) m / k;
	for(int j = 0; j < k - 1; j++){
		punto2.second = valor;
		valor += (double) m / k;

		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	// ahora los k rayos hacia abajo
	punto2.second = 0;
	valor = (double) n / k;
	for(int j = 0; j < k; j++){
		punto2.first = valor;
		valor += (double) n / k;

		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	return res;
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

/*
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
*/

void testTomo(){
	string path = "exp_nipo/in/resize_tomo1.csv";
	TCSimulator Simulator(path, "exp_emi/out/RAYOSHORIZONTALESresize_tomo1_out_32x32.csv", "exp_emi/AVERLAFOTO.csv");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 800);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo2 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 800);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo3 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 800);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo4 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 800);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo5 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 800);
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo2.begin(), rayosTomo2.end());
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo3.begin(), rayosTomo3.end());
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo4.begin(), rayosTomo4.end());
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo5.begin(), rayosTomo5.end());

	vector<double> nuevaImagen = Simulator.obtenerImagenPorRayos(rayosTomo1, 0, 4, 0);
	// vector<double> carlos = csvToVector(32, 32, "resize_tomo1_out2_32x32");
	// mostrarVector(carlos);
}


int main(){
	//Test1ParaMult();
	//TestParaAplanar();
	testTomo();
	//testObtenerImagen();
	return 1;
}