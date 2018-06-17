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

void mostrarVectorPairDoubleNipo(vector<pair<double, double> >& vec){
	cout << "[";
	for (int i = 0; i < vec.size() - 1; ++i)
	{
		cout << "(" << vec[i].first << "," << vec[i].second << "), ";
	}
	cout << "(" << vec[vec.size() - 1].first << "," << vec[vec.size() - 1].second << ")]";
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

// FALTA CORREGIR QUE RAND SEA UN FLOAT, LA FUNCIÓN QUE CONOCEMOS DEVUELVE UN ENTERO

// m pixeles de altura, n pixeles de ancho
// genera dado un punto fijo al azar en el algún extremo
// (pos = 0 extremo izquierdo, pos = 1 extremo arriba, pos = 2 extremo derecho, pos = 3 extremo abajo)
// k rayos 'bien distribuidos' desde ese punto fijo hacia cada uno de los otros extremos
// ej: si pos = 0, genera un punto random en el extremo izquierdo y crea k rayos para arriba, k rayos para la derecha, y k rayos para abajo (en realidad en alguno de los 3 genera k-1 rayos)
// la salida contiene siempre vec[0] = 1er punto rayo 1, vec[1] = 2do punto rayo 1, vec[2] = primer punto rayo 2, .......
vector<pair<double, double> > generadorRayosPuntoFijo(int m, int n, int k, int pos){
	pair<double, double> punto1;
	pair<double, double> punto2;
	vector<pair<double, double> > res;

	if(pos == 0){
		// primer punto en el extremo izquierdo.
		// genero un punto en cualquier lado del extremo izquierdo
		punto1.first = 0;
		punto1.second = rand() % n;
		if(punto1.second == 0) punto1.second++;

		// arranco por generar los k rayos hacia arriba
		punto2.second = m;
		double valor = (double) n / k;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += (double) n / k;
			res.push_back(punto1);
			res.push_back(punto2);
		}

		// ahora los k rayos hacia la derecha. Freno uno antes porque sino repito un punto
		punto2.first = m;
		valor = (double) m / k;
		for(int j = 0; j < k - 1; j++){
			punto2.second = valor;
			valor += (double) m / k;
			res.push_back(punto1);
			res.push_back(punto2);
		}

		// ahora los k rayos hacia abajo
		punto2.second = 0;
		valor = (double) n / k;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += (double) n / k;
			res.push_back(punto1);
			res.push_back(punto2);
		}
	}

	if(pos == 1){
		// primer punto en el extremo de arriba. Para este caso tengo que tener bien en cuenta
		// el tema de que x1 tiene que ser menor que x2
		punto1.first = rand() % n;
		punto1.second = m;
		if(punto1.first == 0) punto1.first++;

		// genero k rayos hacia la derecha. Freno uno antes porque sino me queda rayo recto
		punto2.first = m;
		double valor = (double) m / k;
		for(int j = 0; j < k - 1; j++){
			punto2.second = valor;
			valor += (double) m/k;
			res.push_back(punto1);
			res.push_back(punto2);
		}

		// genero k rayos hacia abajo
		punto2.second = 0;
		valor = (double) n / k;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += (double) n/k;
			if(punto1.first <= punto2.first){
				res.push_back(punto1);
				res.push_back(punto2);
			}else{
				res.push_back(punto2);
				res.push_back(punto1);
			}			
		}

		// genero k rayos hacia la izquierda. Pusheo primero el punto 2 pues este tiene x más chico
		punto2.first = 0;
		valor = 0;
		for(int j = 0; j < k; j++){
			punto2.second = valor;
			valor += (double) m / k;
			res.push_back(punto2);
			res.push_back(punto1);
		}
	}

	if(pos == 2){
		// primer punto en el extremo de la derecha. Para este caso siempre pusheo el punto 2 antes
		punto1.first = n;
		punto1.second = rand() % m;
		if(punto1.second == 0) punto1.second++;

		// genero k rayos hacia abajo
		punto2.second = 0;
		double valor = 0;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += n/k;
			res.push_back(punto2);
			res.push_back(punto1);
		}

		// genero k rayos hacia la izquierda
		punto2.first = 0;
		valor = (double) m / k;
		for(int j = 0; j < k; j++){
			punto2.second = valor;
			valor += (double) m / k;
			res.push_back(punto2);
			res.push_back(punto1);
		}

		// genero k rayos hacia arriba. Freno uno antes
		punto2.second = m;
		 valor = (double) n / k;
		for(int j = 0; j < k - 1; j++){
			punto2.first = valor;
			valor += (double) n / k;
			res.push_back(punto2);
			res.push_back(punto1);
		}
	}

	if(pos == 3){
		// primer punto en el extremo de abajo. Para este caso tener cuidado a ver cuál pusheo primero
		punto1.first = rand() % n;
		punto1.second = 0;
		if(punto1.first == 0) punto1.first++;

		// genero k rayos hacia la izquierda
		punto2.first = 0;
		double valor = (double) m / k;
		for(int j = 0; j < k; j++){
			punto2.second = valor;
			valor += (double) m / k;
			res.push_back(punto2);
			res.push_back(punto1);
		}

		// genero k rayos hacia arriba
		punto2.second = m;
		valor = (double) n / k;
		for(int j = 0; j < k; j++){
			punto2.first = valor;
			valor += (double) n / k;
			if(punto1.first > punto2.first){
				res.push_back(punto2);
				res.push_back(punto1);				
			}else{
				res.push_back(punto1);
				res.push_back(punto2);
			}
		}

		// g enero k rayos hacia la derecha. Freno uno antes
		punto2.first = m;
		valor = (double) m / k;
		for(int j = 0; j < k - 1; j++){
			punto2.second = valor;
			valor += (double) m/k;
			res.push_back(punto1);
			res.push_back(punto2);
		}		
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
	vector<pair<double, double> > carlos = generadorRayosPuntoFijo(5, 5, 5, 3);
	// mostrarVectorPairDoubleNipo(carlos);
	// cout << carlos.size() << endl;
	return 0;
}