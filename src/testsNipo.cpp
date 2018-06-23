#include "Image.cpp"
#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include <experimental/filesystem>
#include "matrizRala.h"

using namespace std;

// función para randoms en double
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void mostrarVectorPairDoubleNipo(vector<pair<double, double> >& vec){
	cout << "[";
	for (int i = 0; i < vec.size() - 1; ++i)
	{
		cout << "(" << vec[i].first << "," << vec[i].second << "), ";
	}
	cout << "(" << vec[vec.size() - 1].first << "," << vec[vec.size() - 1].second << ")]";
	cout << endl;
}

void mostrarVectorPairPairDoubleNipo(vector<pair<pair<double, double>, pair<double, double> > >& vec){
	cout << "[";
	for (int i = 0; i < vec.size() - 1; ++i)
	{
		cout << "(" << vec[i].first.first << "," << vec[i].first.second << "), ";
		cout << "(" << vec[i].second.first << "," << vec[i].second.second << "), ";
	}
	cout << "(" << vec[vec.size() - 1].first.first << "," << vec[vec.size() - 1].first.second << "), ";
	cout << "(" << vec[vec.size() - 1].second.first << "," << vec[vec.size() - 1].second.second << ")]";
	cout << endl;
}

double ECM(vector<double> v1, vector<double> v2){
	double res = 0;
	for(int i = 0; i < v1.size(); i++){
		res += pow((v1[i] - v2[i]), 2);
	}
	res = res / v1.size();
	return res;
}

// como entrada toma el orden de magnitud de la discretización,
// el simulador con los rayos ya creados, y un entero para devolver el ECM ahí
// adentro discretiza los rayos, resuelve CM, calcula el ECM entre la nueva imagen y la origial, 
// y devuelve la imagen discretizada
// Image* regenerarImagenConDiscretizacionNipo(int ordenDeMagnitud, TCSimulator& Simulator, double ECM){
// 	int n = Simulator.rayos.size();
// 	Rala A = Rala(n, Simulator.getWidth()*Simulator.getHeight());
// 	A.conex = vector< map<int, double> >();
// 	for(int i = 0 ; i < n ; i ++){
// 		Rala rayosoDiscretizado = Rala(Simulator.getWidth()/ordenDeMagnitud, Simulator.getHeight()/ordenDeMagnitud);

// 		Simulator.discretizarMatrizDireccionesEnOrdenDe(Simulator.rayos[i], rayoDiscretizado, ordenDeMagnitud);

// 		A.conex.push_back(Simulator.convertirRayoEnFila(rayoDiscretizado));
// 	}
// 	vector<double> imagenAplanada = Simulator.resolverCM(A, Simulator.tiempos);

// 	// discretizo la original

// 	// calculo ECM


// 	Image* res = new Image();
// 	res->height = Simulator.getWidth()/ordenDeMagnitud;
// 	res->width = Simulator.getHeight()/ordenDeMagnitud;
// 	uchar* newBuffer = new uchar[res->height*res->width*3];
// 	for(int fila = 0; fila  < res->height; fila++){
// 		for(int col = 0; col < res->width; col++){
// 			newBuffer[fila*col*3+green] = imagenAplanada[fila*col];
// 			newBuffer[fila*col*3+red] = imagenAplanada[fila*col];
// 			newBuffer[fila*col*3+blue] = imagenAplanada[fila*col];
// 		}
// 	}
// 	res->imageBuffer = newBuffer;
// 	return res;
// }

// m pixeles de altura, n pixeles de ancho
// genera dado un punto fijo al azar en el algún extremo
// (pos = 0 extremo izquierdo, pos = 1 extremo arriba, pos = 2 extremo derecho, pos = 3 extremo abajo)
// k rayos 'bien distribuidos' desde ese punto fijo hacia cada uno de los otros extremos
// ej: si pos = 0, genera un punto random en el extremo izquierdo y crea k rayos para arriba, k rayos para la derecha, y k rayos para abajo (en realidad en alguno de los 3 genera k-1 rayos)
// la salida contiene siempre vec[0] = 1er punto rayo 1, vec[1] = 2do punto rayo 1, vec[2] = primer punto rayo 2, .......
vector<pair<pair<double,double>, pair<double,double> > > generadorRayosPuntoFijo(int m, int n, int k, int pos){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<pair<double, double>, pair<double, double> > pixel1;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	if(pos == 0){
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
	}

	if(pos == 1){
		// primer punto en el extremo de arriba. Para este caso tengo que tener bien en cuenta
		// el tema de que x1 tiene que ser menor que x2
		punto1.first = fRand(0, (double) n);
		punto1.second = m;
		if(punto1.first == 0) punto1.first += 0.1;

		// genero k rayos hacia la derecha. Freno uno antes porque sino me queda rayo recto
		punto2.first = n;
		double valor = (double) m / k;
		for(int j = 0; j < k - 1; j++){
			punto2.second = valor;
			valor += (double) m/k;

			pixel1.first = punto1;
			pixel1.second = punto2;
			res.push_back(pixel1);
		}

		// genero k rayos hacia abajo
		punto2.second = 0;
		valor = (double) n / k;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += (double) n/k;
			if(punto1.first <= punto2.first){
				pixel1.first = punto1;
				pixel1.second = punto2;
			}else{
				pixel1.first = punto2;
				pixel1.second = punto1;
			}
			res.push_back(pixel1);
		}

		// genero k rayos hacia la izquierda. Pusheo primero el punto 2 pues este tiene x más chico
		punto2.first = 0;
		valor = 0;
		for(int j = 0; j < k; j++){
			punto2.second = valor;
			valor += (double) m / k;

			pixel1.first = punto2;
			pixel1.second = punto1;

			res.push_back(pixel1);
		}
	}

	if(pos == 2){
		// primer punto en el extremo de la derecha. Para este caso siempre pusheo el punto 2 antes
		punto1.first = n;
		punto1.second = fRand(0, (double) m);
		if(punto1.second == 0) punto1.second += 0.1;
		pixel1.second = punto1;

		// genero k rayos hacia abajo
		punto2.second = 0;
		double valor = 0;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += n/k;

			pixel1.first = punto2;
			res.push_back(pixel1);
		}

		// genero k rayos hacia la izquierda
		punto2.first = 0;
		valor = (double) m / k;
		for(int j = 0; j < k; j++){
			punto2.second = valor;
			valor += (double) m / k;

			pixel1.first = punto2;
			res.push_back(pixel1);
		}

		// genero k rayos hacia arriba. Freno uno antes
		punto2.second = m;
		valor = (double) n / k;
		for(int j = 0; j < k - 1; j++){
			punto2.first = valor;
			valor += (double) n / k;

			pixel1.first = punto2;
			res.push_back(pixel1);
		}
	}

	if(pos == 3){
		// primer punto en el extremo de abajo. Para este caso tener cuidado a ver cuál pusheo primero
		punto1.first = fRand(0, (double) n);
		punto1.second = 0;
		if(punto1.first == 0) punto1.first += 0.1;

		// genero k rayos hacia la izquierda
		punto2.first = 0;
		double valor = (double) m / k;
		for(int j = 0; j < k; j++){
			punto2.second = valor;
			valor += (double) m / k;

			pixel1.first = punto2;
			pixel1.second = punto1;
			res.push_back(pixel1);
		}

		// genero k rayos hacia arriba
		punto2.second = m;
		valor = (double) n / k;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += (double) n / k;

			if(punto1.first > punto2.first){
				pixel1.first = punto2;
				pixel1.second = punto1;			
			}else{
				pixel1.first = punto1;
				pixel1.second = punto2;
			}
		}

		// genero k rayos hacia la derecha. Freno uno antes
		punto2.first = n;
		valor = (double) m / k;
		for(int j = 0; j < k - 1; j++){
			punto2.second = valor;
			valor += (double) m/k;

			pixel1.first = punto1;
			pixel1.second = punto2;
			res.push_back(pixel1);
		}		
	}

	return res;
}

vector<pair<pair<double,double>, pair<double,double> > > generadorRayosCruzados(int m, int n, int k){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<pair<double, double>, pair<double, double> > pixel1;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	// arranco por los cruzados de izquierda hacia arriba
	punto1.first = 0;
	punto2.second = m;
	double valor1 = (double) k * m / (k + 1);
	double valor2 = (double) n / (k + 1);
	for(int i = 0; i < k; i++){
		punto1.second = valor1;
		punto2.first = valor2;
		valor1 -= (double) m / (k+1);
		valor2 += (double) n / (k+1);

		pixel1.first = punto1;
		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	// ahora los cruzados desde abajo hacia la derecha
	punto1.second = 0;
	punto2.first = n;
	valor1 = (double) n / (k + 1);
	valor2 = (double) k * m / (k+1);
	for(int i = 0; i < k; i++){
		punto1.first = valor1;
		punto2.second = valor2;
		valor1 += (double) n / (k+1);
		valor2 -= (double) m / (k+1);

		pixel1.first = punto1;
		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	return res;
}

// es necesario que k siempre sea par porque sino te quedan dos rayos que son rectas constantes
vector<pair<pair<double,double>, pair<double,double> > > generadorRayosOpuestos(int m, int n, int k){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<double, double> punto3;
	pair<double, double> punto4;
	pair<pair<double, double>, pair<double, double> > pixel1;
	pair<pair<double, double>, pair<double, double> > pixel2;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	punto1.first = 0;
	punto2.first = n;
	punto3.second = 0;
	punto4.second = n;

	double valor1 = (double) k * m / (k + 1);
	double valor2 = (double) m / (k + 1);
	double valor3 = (double) n / (k + 1);
	double valor4 = (double) k * n / (k + 1);

	for(int i = 0; i < k; i++){
		punto1.second = valor1;
		punto2.second = valor2;
		punto3.first = valor3;
		punto4.first = valor4;
		valor1 -= (double) m / (k+1);
		valor2 += (double) m / (k+1);
		valor3 += (double) n / (k+1);
		valor4 -= (double) n / (k+1);

		pixel1.first = punto1;
		pixel1.second = punto2;

		if(punto3.first <= punto4.first){
			pixel2.first = punto3;
			pixel2.second = punto4;
		}else{
			pixel2.first = punto4;
			pixel2.second = punto3;
		}

		res.push_back(pixel1);
		res.push_back(pixel2);
	}

	return res;
}

void testsECM(){
	vector<double> vector1(3, 0.0);
	vector<double> vector2(3, 0.0);
	vector1[0] = 2;
	vector1[1] = 3;
	vector1[2] = 1;
	vector2[0] = 0;
	vector2[1] = 3;
	vector2[2] = 1;

	cout << ECM(vector1, vector2) << endl;
	// debe coutear 4/3. funciona OK parece
}

// hace el generador de rayos opuestos variando el porcentaje de rayos desde 5 hasta kMax, fijando tres p de ruido. Todo con la ppm de la cátedra de 100x100. Compara ECM
// para elegir la cantidad k de rayos tomo el porcentaje de rayos que quiero según el máximo entre el alto y el ancho
// FALTA PONERLE CHRONO TAMBIÉN PARA TOMAR TIEMPO Y VER QUÉ ONDA LA DISCRETIZACIÓN
void testRayosOpuestosTomosCatedra(int kMax){
	fstream sal1("exp_nipo/opuestosTomo1.csv", ios::out);
	// fstream sal2("tests_nipo/opuestosTomo2.csv", ios::out);
	// fstream sal3("tests_nipo/opuestosTomo3.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	// sal2 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	// sal3 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "../imgs_TC/tomo.ppm";
	// string path2 = "imgs_TC/tomo2.ppm";
	// string path3 = "imgs_TC/tomo3.ppm";

	TCSimulator Simulator1(path1);
	// TCSimulator Simulator2(path2);
	// TCSimulator Simulator3(path3);

	for(int i = 5; i < kMax; i = i + 5){
		cout << "Voy por porcentaje = " << i << endl;

		int dimMax1 = max(Simulator1.getHeight(), Simulator1.getWidth());
		int k1 = round((double) dimMax1 * kMax / 100);
		// me aseguro que k1 siempre sea par para no tener las rectas constantes
		if(k1 % 2 == 1) k1++;

		// int dimMax2 = max(Simulator2.getHeight(), Simulator2.getWidth());
		// int k2 = round((double) dimMax2 * kMax / 100);
		// me aseguro que k2 siempre sea par para no tener las rectas constantes
		// if(k2 % 2 == 1) k2++;

		// int dimMax3 = max(Simulator3.getHeight(), Simulator3.getWidth());
		// int k3 = round((double) dimMax3 * kMax / 100);
		// me aseguro que k3 siempre sea par para no tener las rectas constantes
		// if(k3 % 2 == 1) k3++;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator1.getHeight(), Simulator1.getWidth(), k1);
		// vector<pair<pair<double, double>, pair<double, double> > > rayosTomo2 = generadorRayosOpuestos(Simulator2.getHeight(), Simulator2.getWidth(), k2);
		// vector<pair<pair<double, double>, pair<double, double> > > rayosTomo3 = generadorRayosOpuestos(Simulator3.getHeight(), Simulator3.getWidth(), k3);

		for(int j = 0; j < 10; j++){
			// lo hago 10 veces para tomar promedio de tiempos

			// acá llamo a función de Emi resultora de todo

			// acá llamo a ECM comparando el vector original con el vector resultado. Faltaría discretizar también el vector original, y ver qué onda la discretización

			// sal1 << Simulator1.getHeight() << "," << Simulator1.getWidth() << "," << i << "," << ecm1 << "," << tiempo1 << endl;
			// sal2 << Simulator2.getHeight() << "," << Simulator2.getWidth() << "," << i << "," << ecm2 << "," << tiempo2 << endl;
			// sal3 << Simulator3.getHeight() << "," << Simulator3.getWidth() << "," << i << "," << ecm3 << "," << tiempo3 << endl;
		}
	}

	sal1.close();
	// sal2.close();
	// sal3.close();
}

// hace el generador de rayos cruzados variando el porcentaje de rayos desde 5 hasta kMax, fijando tres p de ruido. Todo con las 3 tomografías de la cátedra. Compara ECM
// para elegir la cantidad k de rayos tomo el porcentaje de rayos que quiero según el máximo entre el alto y el ancho
// FALTA PONERLE CHRONO TAMBIÉN PARA TOMAR TIEMPO Y VER QUÉ ONDA LA DISCRETIZACIÓN Y SI SÓLO ME QUEDO CON TOMO1
void testRayosCruzadosTomosCatedra(int kMax){
	fstream sal1("tests_nipo/cruzadosTomo1.csv", ios::out);
	fstream sal2("tests_nipo/cruzadosTomo2.csv", ios::out);
	fstream sal3("tests_nipo/cruzadosTomo3.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	sal2 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	sal3 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "imgs_TC/tomo.ppm";
	string path2 = "imgs_TC/tomo2.ppm";
	string path3 = "imgs_TC/tomo3.ppm";

	TCSimulator Simulator1(path1);
	TCSimulator Simulator2(path2);
	TCSimulator Simulator3(path3);

	for(int i = 5; i < kMax; i = i + 5){
		cout << "Voy por porcentaje = " << i << endl;

		int dimMax1 = max(Simulator1.getHeight(), Simulator1.getWidth());
		int k1 = round((double) dimMax1 * kMax / 100);

		int dimMax2 = max(Simulator2.getHeight(), Simulator2.getWidth());
		int k2 = round((double) dimMax2 * kMax / 100);

		int dimMax3 = max(Simulator3.getHeight(), Simulator3.getWidth());
		int k3 = round((double) dimMax3 * kMax / 100);

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);
		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo2 = generadorRayosCruzados(Simulator2.getHeight(), Simulator2.getWidth(), k2);
		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo3 = generadorRayosCruzados(Simulator3.getHeight(), Simulator3.getWidth(), k3);

		for(int j = 0; j < 10; j++){
			// lo hago 10 veces para tomar promedio de tiempos

			// acá llamo a función de Emi resultora de todo

			// acá llamo a ECM comparando el vector original con el vector resultado. Faltaría discretizar también el vector original, y ver qué onda la discretización

			// sal1 << Simulator1.getHeight() << "," << Simulator1.getWidth() << "," << i << "," << ecm1 << "," << tiempo1 << endl;
			// sal2 << Simulator2.getHeight() << "," << Simulator2.getWidth() << "," << i << "," << ecm2 << "," << tiempo2 << endl;
			// sal3 << Simulator3.getHeight() << "," << Simulator3.getWidth() << "," << i << "," << ecm3 << "," << tiempo3 << endl;
		}
	}

	sal1.close();
	sal2.close();
	sal3.close();
}

// hace el generador de rayos cruzados variando el porcentaje de rayos desde 5 hasta kMax, fijando tres p de ruido. Todo con las 3 tomografías de la cátedra. Compara ECM
// para elegir la cantidad k de rayos tomo el porcentaje de rayos que quiero según el máximo entre el alto y el ancho
// FALTA PONERLE CHRONO TAMBIÉN PARA TOMAR TIEMPO Y VER QUÉ ONDA LA DISCRETIZACIÓN Y SI SÓLO ME QUEDO CON TOMO1
void testRayosFijosTomosCatedra(int kMax){
	fstream sal1("tests_nipo/fijosTomo1.csv", ios::out);
	fstream sal2("tests_nipo/fijosTomo2.csv", ios::out);
	fstream sal3("tests_nipo/fijosTomo3.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	sal2 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	sal3 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "imgs_TC/tomo.ppm";
	string path2 = "imgs_TC/tomo2.ppm";
	string path3 = "imgs_TC/tomo3.ppm";

	TCSimulator Simulator1(path1);
	TCSimulator Simulator2(path2);
	TCSimulator Simulator3(path3);

	for(int i = 5; i < kMax; i = i + 5){
		cout << "Voy por porcentaje = " << i << endl;

		int dimMax1 = max(Simulator1.getHeight(), Simulator1.getWidth());
		int k1 = round((double) dimMax1 * kMax / 100);

		int dimMax2 = max(Simulator2.getHeight(), Simulator2.getWidth());
		int k2 = round((double) dimMax2 * kMax / 100);

		int dimMax3 = max(Simulator3.getHeight(), Simulator3.getWidth());
		int k3 = round((double) dimMax3 * kMax / 100);

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijo(Simulator1.getHeight(), Simulator1.getWidth(), k1, 0);
		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo2 = generadorRayosPuntoFijo(Simulator2.getHeight(), Simulator2.getWidth(), k2, 0);
		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo3 = generadorRayosPuntoFijo(Simulator3.getHeight(), Simulator3.getWidth(), k3, 0);

		for(int j = 0; j < 10; j++){
			// lo hago 10 veces para tomar promedio de tiempos

			// acá llamo a función de Emi resultora de todo

			// acá llamo a ECM comparando el vector original con el vector resultado. Faltaría discretizar también el vector original, y ver qué onda la discretización

			// sal1 << Simulator1.getHeight() << "," << Simulator1.getWidth() << "," << i << "," << ecm1 << "," << tiempo1 << endl;
			// sal2 << Simulator2.getHeight() << "," << Simulator2.getWidth() << "," << i << "," << ecm2 << "," << tiempo2 << endl;
			// sal3 << Simulator3.getHeight() << "," << Simulator3.getWidth() << "," << i << "," << ecm3 << "," << tiempo3 << endl;
		}
	}

	sal1.close();
	sal2.close();
	sal3.close();
}


// ejemplo para iterar los csvs para abrir
// void correrTestsPracticaEj2(){			// salvo los de entrada 200, son todos correctos.
// 	std::chrono::time_point<std::chrono::system_clock> start, end;

// 	fstream s ("salidasTestsCatedra.txt", ios::out);
// 	for(int i = 1; i < 15; i++){
// 		string st = "t" + std::to_string(i);
// 		if(st != "t4"){
// 			fstream e (st, ios::in);
// 			int n;
// 			e >> n;
// 			std::vector<int> ent(n);
// 			int aux;
// 			for(int j = 0; j < n; j++){
// 				e >> aux;
// 				ent[j] = aux;
// 			}
// 			start = std::chrono::system_clock::now();
// 			int res = Ej2(ent, n);
// 			end = std::chrono::system_clock::now();
// 			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;			
// 			s << res;
// 			s << ",";
// 			s << elapsed_seconds.count() << endl;
// 		}
// 	}
// }

void crearCSVs(Rala&A){
	ofstream ata;

	//nombreHardcodeado para no cambiar parametros de entrada
	ata.open ("AtA.csv");

	for (int i = 0; i < A.n; ++i)
	{
		for (int j = 0; j < A.m; ++j)
		{
			map<int,double>::iterator it = A.conex[i].find(j);
			if (it != A.conex[i].end())
			{
				ata << it->second;
			}else{
				ata << "0";
			}

			if(j == (A.m - 1)){ ata << "\n";} else { ata << ",";}
		}
	}

	ata.close();
}

void testAsd(){
	string path = "exp_nipo/test.csv";
	TCSimulator Simulator(path);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator.getHeight(), Simulator.getWidth(), 10);
	Simulator.generarRayos(20, rayosTomo1);
	Image* nuevaImagen = Simulator.regenerarImagen();
	nuevaImagen->SaveImage("exp_nipo/in/testCM.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);
	delete nuevaImagen;
}

void testAsf(){
	string path = "exp_nipo/in/testCM.ppm";
	TCSimulator Simulator(path);
	// Simulator.imageMatrix->convertToCSV("exp_nipo/tomo");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator.getHeight(), Simulator.getWidth(), 150);
	vector<pair<pair<double, double>, pair<double, double> > > asd;
	Simulator.generarRayos(50, asd);
	Image* nuevaImagen = Simulator.regenerarImagen();
	nuevaImagen->SaveImage("exp_nipo/in/juan.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);
}


int main(){
	srand(time(NULL));
	// iterateCSVs();
	// vector<pair<pair<double, double>, pair<double, double> > > carlos = generadorRayosPuntoFijo(5, 5, 5, 0);
	// mostrarVectorPairPairDoubleNipo(carlos);
	// cout << carlos.size() << endl;
	// vector<pair<pair<double, double>, pair<double, double> > > cruzados = generadorRayosCruzados(10, 5, 4);
	// mostrarVectorPairPairDoubleNipo(cruzados);
	// vector<pair<pair<double, double>, pair<double, double> > > opuestos = generadorRayosOpuestos(10, 5, 4);
	// mostrarVectorPairPairDoubleNipo(opuestos);
	// cout << fRand(0.5, 5.3) << endl;
	// testAsd();
	testAsf();
	return 0;
}