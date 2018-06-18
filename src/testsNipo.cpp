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

// funciona sólo para imágenes cuadradas, por eso solo hay que pasarle el n
vector<pair<pair<double,double>, pair<double,double> > > generadorRayosCruzados(int n, int k){
	pair<double, double> punto1;
	pair<double, double> punto2;
	pair<pair<double, double>, pair<double, double> > pixel1;
	vector<pair<pair<double,double>, pair<double,double> > > res;

	// arranco por los cruzados de izquierda hacia arriba
	punto1.first = 0;
	punto2.second = n;
	double valor1 = (double) k * n / (k + 1);
	double valor2 = (double) n / (k + 1);
	for(int i = 0; i < k; i++){
		punto1.second = valor1;
		punto2.first = valor2;
		valor1 -= (double) n / (k+1);
		valor2 += (double) n / (k+1);

		pixel1.first = punto1;
		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	// ahora los cruzados desde abajo hacia la derecha
	punto1.second = 0;
	punto2.first = n;
	valor1 = (double) n / (k + 1);
	valor2 = (double) k * n / (k+1);
	for(int i = 0; i < k; i++){
		punto1.first = valor1;
		punto2.second = valor2;
		valor1 += (double) n / (k+1);
		valor2 -= (double) n / (k+1);

		pixel1.first = punto1;
		pixel1.second = punto2;
		res.push_back(pixel1);
	}

	return res;
}

// funciona sólo para imágenes cuadradas, por eso solo hay que pasarle el n
vector<pair<pair<double,double>, pair<double,double> > > generadorRayosOpuestos(int n, int k){
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

	double valor1 = (double) k * n / (k + 1);
	double valor2 = (double) n / (k + 1);
	double valor3 = (double) n / (k + 1);
	double valor4 = (double) k * n / (k + 1);

	for(int i = 0; i < k; i++){
		punto1.second = valor1;
		punto2.second = valor2;
		punto3.first = valor2;
		punto4.first = valor1;
		valor1 -= (double) n / (k+1);
		valor2 += (double) n / (k+1);

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

int main(){
	srand(time(NULL));
	// vector<pair<pair<double, double>, pair<double, double> > > carlos = generadorRayosPuntoFijo(5, 5, 5, 0);
	// mostrarVectorPairPairDoubleNipo(carlos);
	// cout << carlos.size() << endl;
	// vector<pair<pair<double, double>, pair<double, double> > > cruzados = generadorRayosCruzados(5, 4);
	// mostrarVectorPairPairDoubleNipo(cruzados);
	// vector<pair<pair<double, double>, pair<double, double> > > opuestos = generadorRayosOpuestos(5, 4);
	// mostrarVectorPairPairDoubleNipo(opuestos);
	// cout << fRand(0.5, 5.3) << endl;
	return 0;
}