// #include "Image.cpp"
#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"
#include "auxiliar.h"

using namespace std;

// función para randoms en double
double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

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

void mostrarMatrizNipo(vector<vector<double> >& matriz){
	int n = matriz.size();
	int m = matriz[0].size();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cout << matriz[i][j] << " " ;
		}
		cout << endl;
	}
}

vector<int> aplanarImagen(vector<vector<int> > vecEntrada){
	vector<int> res;
	for(int i = 0; i < vecEntrada.size(); i++){
		for(int j = 0; j < vecEntrada[i].size(); j++){
			res.push_back(vecEntrada[i][j]);
		}
	}
	return res;
}

vector<double> vectorIntToVectorDouble(vector<int>& vec){
	vector<double> res;
	for(int i = 0; i < vec.size(); i++){
		res.push_back((double) vec[i]);
	}
	return res;
}

int llenarRenglonNipo(vector<int>& pixeles, string renglon){
	int n = renglon.length();
	int lastComa = 0 ;
	for(int i = 0 ; i < n ; i ++){
		if(renglon[i] == ','){
			pixeles.push_back(stoi(renglon.substr(lastComa,i-lastComa)));
		 	lastComa = i+1;
		}
	}
	pixeles.push_back(stoi(renglon.substr(lastComa,n-lastComa)));
	return pixeles.size();
}

vector<int> csvToVector(string path){
	string pathF = path+".csv";
	filebuf fb;
	fb.open (pathF,std::ios::in);
	std::istream fs (&fb);

    string s;
    vector<string> renglones; 
    int cantDeRenglones = 0 ;
    int cantElementosPorRenglon = 0;
    while(getline(fs,s)){
        renglones.push_back(s);
        cantDeRenglones ++;
    }

    vector<vector<int> > pixeles;
    for(int i = 0 ;i < cantDeRenglones; i++){
    	pixeles.push_back(std::vector<int> ());
    }
    for(int i = 0 ;i < cantDeRenglones; i ++){
    	cantElementosPorRenglon = llenarRenglonNipo(pixeles[i], renglones[i]);
    }

    vector<int> res = aplanarImagen(pixeles);

    return res;
}

void generarCSVVectorPairPair(vector<pair<pair<double, double>, pair<double, double> > > V, string name){
	ofstream ata;

	//nombreHardcodeado para no cambiar parametros de entrada
	ata.open (name+".csv"); 

	for (int i = 0; i < V.size(); ++i)
	{
		ata << "(" << V[i].first.first << "," << V[i].first.second << ")";
		ata << " (" << V[i].second.first << "," << V[i].second.second << ")" << endl;
	}

	ata.close();
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

double ECMNipo(vector<double> v1, vector<double> v2){
	double res = 0;
	for(int i = 0; i < v1.size(); i++){
		res += pow((v1[i] - v2[i]), 2);
	}
	res = res / v1.size();
	return res;
}

int pasarDe16a8Nipo(int num){
	return num * 255 / 65235;
}

int pasarDe8a16Nipo(int num){
	return num * 65235 / 255;
}

vector<int> pasarVectorDe16a8Nipo(vector<int>& vec){
	vector<int> res;
	for(int i = 0; i < vec.size(); i++){
		res.push_back(pasarDe16a8Nipo(vec[i]));
	}
	return res;
} 

vector<int> pasarVectorDe8a16Nipo(vector<int>& vec){
	vector<int> res;
	for(int i = 0; i < vec.size(); i++){
		res.push_back(pasarDe8a16Nipo(vec[i]));
	}
	return res;
} 

vector<double> normalizar16BitNipo(vector<int>& vec){
	vector<double> res;
	for(int i = 0; i < vec.size(); i++){
		res.push_back((double) vec[i] / 65235);
	}
	return res;	
}

vector<double> normalizar8BitNipo(vector<int>& vec){
	vector<double> res;
	for(int i = 0; i < vec.size(); i++){
		res.push_back((double) vec[i] / 255);
	}
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

// para esta agregar en generarRayos, dentro del for de rayosDefinidos: mostrarRala(&rayos[i]); cout << endl;
void verSiCruzadosBien(){
	string path = "exp_nipo/out/testCM.csv";
	TCSimulator Simulator(path, "exp_nipo/out/regenerada.csv");
	// Simulator.imageMatrix->convertToCSV("exp_nipo/tomo");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator.getHeight(), Simulator.getWidth(), 7);
	// cout << rayosTomo1.size() << endl;
	vector<pair<pair<double, double>, pair<double, double> > > asd;
	Simulator.generarRayos(14, rayosTomo1);
	Image nuevaImagen = Simulator.regenerarImagenConDiscretizacion(1);	
}

// para esta agregar en generarRayos, dentro del for de rayosDefinidos: mostrarRala(&rayos[i]); cout << endl;
void verSiOpuestosBien(){
	string path = "exp_nipo/out/testCM.csv";
	TCSimulator Simulator(path, "exp_nipo/out/regenerada_opuestos.csv");
	// Simulator.imageMatrix->convertToCSV("exp_nipo/tomo");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator.getHeight(), Simulator.getWidth(), 50);
	cout << rayosTomo1.size() << endl;
	vector<pair<pair<double, double>, pair<double, double> > > asd;
	Simulator.generarRayos(100, rayosTomo1);
	Image nuevaImagen = Simulator.regenerarImagenConDiscretizacion(1);	
}
// parece que voy a tener que llegar a más del 200% porque está jodido esto.

void testsECM(){
	vector<double> vector1(3, 0);
	vector<double> vector2(3, 0);
	vector1[0] = 2;
	vector1[1] = 3;
	vector1[2] = 1;
	vector2[0] = 0;
	vector2[1] = 3;
	vector2[2] = 1;

	cout << ECM(vector1, vector2) << endl;
	// debe coutear 4/3. funciona OK parece
}

// hace el generador de rayos opuestos variando el porcentaje de rayos con respecto a la cantidad de pixeles de la discretización desde
// 100% hasta kMax, incluyendo a este último (probablemente kMax = 20 y 110% se considere 1) fijando un ruido de 0.1.
// Todo con la png de la cátedra de 100x100. Compara ECM
void testRayosOpuestosTomosCatedra(int kMax, int ordenMagnitud){
	cout << "Arranca rayos opuestos" << endl;

	fstream sal1("exp_nipo/opuestosTomo1_capFinal.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");
	// imagenOriginalReducida está en 8 bits

	TCSimulator Simulator1(path1, "exp_nipo/out/exp_opuestos/out1CapPro.csv", "exp_nipo/rayos_out/rayo0");

	int cantPixelesDiscretizacion = Simulator1.getHeight() * Simulator1.getWidth() / (ordenMagnitud * ordenMagnitud);

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;
		// me aseguro que k1 siempre sea par para no tener las rectas constantes
		if(k1 % 2 == 1) k1++;

		cout << k1 << endl;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator1.getHeight(), Simulator1.getWidth(), k1);

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			// acá llamo a función de Emi resultora de todo

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_opuestos/out1CapPro");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaNormalizada = normalizar16BitNipo(nuevaImagenLuegoDeParsear);
			vector<double> originalReducNormalizada = normalizar8BitNipo(imagenOriginalReducida);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;

			// reseteo simulador
			Simulator1.resetSimulator();
		}
	}

	sal1.close();
}

// hace el generador de rayos cruzados variando el porcentaje de rayos con respecto a la cantidad de pixeles de la discretización desde
// 100% hasta kMax, incluyendo a este último (probablemente kMax = 20 y 110% se considere 1) fijando un ruido de 0.1.
// Todo con la png de la cátedra de 100x100. Compara ECM
void testRayosCruzadosTomosCatedra(int kMax, int ordenMagnitud){
	varGlobal = 21;
	cout << "Arranca rayos cruzados" << endl;

	fstream sal1("exp_nipo/cruzadosTomo1_capFinal.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");

	TCSimulator Simulator1(path1, "exp_nipo/out/exp_cruzados/out1_capPro.csv", "exp_nipo/rayos_out/rayo105");

	int cantPixelesDiscretizacion = Simulator1.getHeight() * Simulator1.getWidth() / (ordenMagnitud * ordenMagnitud);

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_cruzados/out1_capPro");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaNormalizada = normalizar16BitNipo(nuevaImagenLuegoDeParsear);
			vector<double> originalReducNormalizada = normalizar8BitNipo(imagenOriginalReducida);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;

			Simulator1.resetSimulator();
		}
	}

	sal1.close();
}

// hace el generador de rayos fijos (fijando pos = 0) variando el porcentaje de rayos con respecto a la cantidad de pixeles de la discretización desde
// 100% hasta kMax, incluyendo a este último (probablemente kMax = 20 y 110% se considere 1) fijando un ruido de 0.1.
// Todo con la png de la cátedra de 100x100. Compara ECM
void testRayosFijosTomosCatedra(int kMax, int ordenMagnitud){
	varGlobal = 42;
	cout << "Arranca rayos fijos" << endl;

	fstream sal1("exp_nipo/fijosTomo1_CapFinal.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");

	TCSimulator Simulator1(path1, "exp_nipo/out/exp_fijos/out1_capPro.csv", "exp_nipo/rayos_out/rayo210.csv");

	int cantPixelesDiscretizacion = Simulator1.getHeight() * Simulator1.getWidth() / (ordenMagnitud * ordenMagnitud);

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = (int) cantRayosAct / 3 + 1;
		if(k1 * 3 - 1 < cantRayosAct) k1++;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijo(Simulator1.getHeight(), Simulator1.getWidth(), k1, 0);

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_fijos/out1_capPro");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaNormalizada = normalizar16BitNipo(nuevaImagenLuegoDeParsear);
			vector<double> originalReducNormalizada = normalizar8BitNipo(imagenOriginalReducida);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;

			Simulator1.resetSimulator();
		}
	}

	sal1.close();
}
// Luego de este vamos a ver que los resultados son muy raros y desiguales, entonces vamos a probar qué punto fijo es mejor (en las puntas, ya sabemos)
// en este vamos a hacer 10 repeticiones para poner puntitos en el gráfico, en los otros dos las 10 repeticiones son solo para tiempos ya que los rayos son siempre iguales
// Para probar qué punto fijo es mejor, divido en cierta cantidad de pedazos el alto y pruebo en todos los pedazos (fijando cierto k). Seguramente mientras más cerca esté de los extremos va a ser mejor
// Quizás también notar que si concatenás varios puntos fijos va genial

// Lo mismo que los 3 anteriores
void testRayosAleatorios(int kMax, int ordenMagnitud){
	cout << "Arranca rayos aleatorios" << endl;

	fstream sal1("exp_nipo/aleatoriosTomo1_capPro.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");

	TCSimulator Simulator1(path1, "exp_nipo/out/exp_aleatorios/out1_capPro.csv", "exp_nipo/rayos_out/rayo315.csv");

	int cantPixelesDiscretizacion = Simulator1.getHeight() * Simulator1.getWidth() / (ordenMagnitud * ordenMagnitud);

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			// string pathSaveFinal = pathSave + to_string(varSavePathInt);

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 1);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_aleatorios/out1_capPro");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaNormalizada = normalizar16BitNipo(nuevaImagenLuegoDeParsear);
			vector<double> originalReducNormalizada = normalizar8BitNipo(imagenOriginalReducida);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;

			Simulator1.resetSimulator();
		}
	}

	sal1.close();
}

void testRayosOpuestosTomosCatedraRayosYCsv(int kMax, int ordenMagnitud){
	cout << "Arranca rayos opuestos" << endl;

	string pathEnt = "exp_nipo/in/tomo.csv";
	string pathSal = "exp_nipo/out/exp_opuestos/csvSalida";
	string rayosSal = "exp_nipo/rayos_out_posta/opuestos/rayo";

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		TCSimulator Simulator1(pathEnt, pathSal + to_string(i) + ".csv", rayosSal + to_string(i) + ".csv");

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		cout << cantRayosAct << endl;
		// me aseguro que k1 siempre sea par para no tener las rectas constantes
		if(k1 % 2 == 1) k1++;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator1.getHeight(), Simulator1.getWidth(), k1);

		vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);

	}
}

void testRayosCruzadosTomosCatedraRayosYCsv(int kMax, int ordenMagnitud){
	cout << "Arranca rayos cruzados" << endl;

	string pathEnt = "exp_nipo/in/tomo.csv";
	string pathSal = "exp_nipo/out/exp_cruzados/csvSalida";
	string rayosSal = "exp_nipo/rayos_out_posta/cruzados/rayo";

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		TCSimulator Simulator1(pathEnt, pathSal + to_string(i) + ".csv", rayosSal + to_string(i) + ".csv");

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		cout << cantRayosAct << endl;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);

		vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);

	}
}

void testRayosFijosTomosCatedraRayosYCsv(int kMax, int ordenMagnitud){
	cout << "Arranca rayos fijos" << endl;

	string pathEnt = "exp_nipo/in/tomo.csv";
	string pathSal = "exp_nipo/out/exp_fijos/csvSalida";
	string rayosSal = "exp_nipo/rayos_out_posta/fijos/rayo";

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		TCSimulator Simulator1(pathEnt, pathSal + to_string(i) + ".csv", rayosSal + to_string(i) + ".csv");

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = (int) cantRayosAct / 3 + 1;
		if(k1 * 3 - 1 < cantRayosAct) k1++;

		cout << cantRayosAct << endl;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijo(Simulator1.getHeight(), Simulator1.getWidth(), k1, 0);

		vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);

	}
}

void testRayosAleatoriosRayosYCsv(int kMax, int ordenMagnitud){
	cout << "Arranca rayos aleatorios" << endl;

	string pathEnt = "exp_nipo/in/tomo.csv";
	string pathSal = "exp_nipo/out/exp_aleatorios/csvSalida";
	string rayosSal = "exp_nipo/rayos_out_posta/aleatorios/rayo";

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		TCSimulator Simulator1(pathEnt, pathSal + to_string(i) + ".csv", rayosSal + to_string(i) + ".csv");

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		cout << cantRayosAct << endl;

		vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);

		vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 1);

	}
}

void testRayosOpuestosTomosCatedraPosta(int kMax, int ordenMagnitud){
	cout << "Arranca rayos opuestos" << endl;

	fstream sal1("exp_nipo/opuestosTomo1_capFinal_EcmGood.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;
	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");
	// imagenOriginalReducida está en 8 bits
	vector<double> imagenOrigDouble = vectorIntToVectorDouble(imagenOriginalReducida);

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;
		// me aseguro que k1 siempre sea par para no tener las rectas constantes
		if(k1 % 2 == 1) k1++;

		cout << cantRayosAct << endl;

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;

			// acá llamo a función de Emi resultora de todo

			TCSimulator Simulator1(path1, "exp_nipo/out/exp_opuestos/out1CapPro_EcmGood.csv");

			vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator1.getHeight(), Simulator1.getWidth(), k1);

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_opuestos/out1CapPro_EcmGood");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaImagenDouble = vectorIntToVectorDouble(nuevaImagenLuegoDeParsear);
			vector<double> nuevaNormalizada = normalizar(nuevaImagenDouble);
			vector<double> originalReducNormalizada = normalizar(imagenOrigDouble);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;
		}
	}

	sal1.close();
}

void testRayosCruzadosTomosCatedraPosta(int kMax, int ordenMagnitud){
	cout << "Arranca rayos cruzados" << endl;

	fstream sal1("exp_nipo/cruzadosTomo1_capFinal_EcmGood.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");
	vector<double> imagenOrigDouble = vectorIntToVectorDouble(imagenOriginalReducida);

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			TCSimulator Simulator1(path1, "exp_nipo/out/exp_cruzados/out1_capPro_EcmGood.csv");

			vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_cruzados/out1_capPro_EcmGood");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaImagenDouble = vectorIntToVectorDouble(nuevaImagenLuegoDeParsear);
			vector<double> nuevaNormalizada = normalizar(nuevaImagenDouble);
			vector<double> originalReducNormalizada = normalizar(imagenOrigDouble);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;
		}
	}

	sal1.close();
}

void testRayosFijosTomosCatedraPosta(int kMax, int ordenMagnitud){
	cout << "Arranca rayos fijos" << endl;

	fstream sal1("exp_nipo/fijosTomo1_CapFinal_EcmGood.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");
	vector<double> imagenOrigDouble = vectorIntToVectorDouble(imagenOriginalReducida);

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = (int) cantRayosAct / 3 + 1;
		if(k1 * 3 - 1 < cantRayosAct) k1++;

		cout << cantRayosAct << endl;

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			TCSimulator Simulator1(path1, "exp_nipo/out/exp_fijos/out1_capPro_EcmGood.csv");

			vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijo(Simulator1.getHeight(), Simulator1.getWidth(), k1, 0);

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 0);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_fijos/out1_capPro_EcmGood");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaImagenDouble = vectorIntToVectorDouble(nuevaImagenLuegoDeParsear);
			vector<double> nuevaNormalizada = normalizar(nuevaImagenDouble);
			vector<double> originalReducNormalizada = normalizar(imagenOrigDouble);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;
		}
	}

	sal1.close();
}

void testRayosAleatoriosPosta(int kMax, int ordenMagnitud){
	cout << "Arranca rayos aleatorios" << endl;

	fstream sal1("exp_nipo/aleatoriosTomo1_capPro_EcmGood.csv", ios::out);

	sal1 << "m,n,pctjeRayos,ECM,tiempo" << endl;

	string path1 = "exp_nipo/in/tomo.csv";
	std::chrono::time_point<std::chrono::system_clock> start, end;

	vector<int> imagenOriginalReducida = csvToVector("exp_nipo/in/resize_tomo");
	vector<double> imagenOrigDouble = vectorIntToVectorDouble(imagenOriginalReducida);

	int cantPixelesDiscretizacion = 25 * 25;

	for(int i = 0; i <= kMax; i++){
		cout << "Voy por porcentaje = " << i << endl;

		int cantRayosAct = (int) round((double) cantPixelesDiscretizacion * (10 + i) / 10);
		int k1 = cantRayosAct / 2;

		cout << cantRayosAct << endl;

		for(int j = 0; j < 5; j++){
			cout << "Voy por j = " << j << endl;
			// lo hago 5 veces para tomar promedio de tiempos

			TCSimulator Simulator1(path1, "exp_nipo/out/exp_aleatorios/out1_capPro_EcmGood.csv");

			vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosCruzados(Simulator1.getHeight(), Simulator1.getWidth(), k1);

			start = std::chrono::system_clock::now();
			vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(rayosTomo1, 0.1, 4, 1);
			end = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			vector<int> nuevaImagenLuegoDeParsear = csvToVector("exp_nipo/out/exp_aleatorios/out1_capPro_EcmGood");
			// en nuevaImagenLuegoDeParsear tengo la nueva en 16 bits

			// calculo ECM normalizando ambas imágenes
			vector<double> nuevaImagenDouble = vectorIntToVectorDouble(nuevaImagenLuegoDeParsear);
			vector<double> nuevaNormalizada = normalizar(nuevaImagenDouble);
			vector<double> originalReducNormalizada = normalizar(imagenOrigDouble);
			double ecm1 = ECM(originalReducNormalizada, nuevaNormalizada);

			sal1 << Simulator1.getHeight() / ordenMagnitud << "," << Simulator1.getWidth() / ordenMagnitud << "," << i * 10 + 100 << "," << ecm1 << "," << elapsed_seconds.count() << endl;

		}
	}

	sal1.close();
}

// fijo 300% rayos aleatorios, 15 imágenes dicom, p = 0.1
void exportAtAyAtb(int cantImages){
	string pathEntrada = "exp_nipo/condition_number_exp/csvs_in/";

	// 


	// levanto 256x256 y discretizo 8 (32x32)
	cout << "Voy por discretización 8" << endl;
	int cantPixelesDiscretizacion = 32*32;
	// for(int i = 0; i < cantImages; i++){
	// 	cout << "Voy por imagen " << i << endl;

	// 	string pathImagenEntrada = pathEntrada + "256x256/" + to_string(i) + ".csv";
	// 	// string pathImagenReducidaSinCsv = pathEntrada + "64x64/" + to_string(i);
	// 	// vector<int> imagenOriginalReducida = csvToVector(pathImagenReducidaSinCsv);
	// 	// vector<double> imagenOriginalDouble = vectorIntToVectorDouble(imagenOriginalReducida);

	// 	// no me importa la imagen de salida porque total voy a conseguirla en octave
	// 	// me importa exportar AtA y Atb, eso se lo tengo que agregar al TCSimulator.h
	// 	TCSimulator Simulator1(pathImagenEntrada, "exp_nipo/juancarlos.csv");

	// 	// creo que el vector vacío de tamaño 300%
	// 	vector<pair<pair<double, double>, pair<double, double> > > vecVacio(cantPixelesDiscretizacion * 3);

	// 	vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(vecVacio, 0.1, 8, 1);

	// 	varGlobalExpNipoCondNumber++;

	// 	// no tengo que calcular el ECM, después puede que lo haga en octave, veremos
	// }

	// levanto 256x256 y lo hago con discretización 4 (o sea 64x64)
	cout << "Voy por discretizacion 4" << endl;
	cantPixelesDiscretizacion = 64*64;
	for(int i = 0; i < cantImages; i++){

		string pathImagenEntrada = pathEntrada + "256x256/" + to_string(i) + ".csv";
		string pathImagenReducidaSinCsv = pathEntrada + "64x64/" + to_string(i);
		vector<int> imagenOriginalReducida = csvToVector(pathImagenReducidaSinCsv);
		vector<double> imagenOriginalDouble = vectorIntToVectorDouble(imagenOriginalReducida);

		// no me importa la imagen de salida porque total voy a conseguirla en octave
		// me importa exportar AtA y Atb, eso se lo tengo que agregar al TCSimulator.h
		TCSimulator Simulator1(pathImagenEntrada, "exp_nipo/juancarlos.csv");

		// creo que el vector vacío de tamaño 300%
		vector<pair<pair<double, double>, pair<double, double> > > vecVacio(cantPixelesDiscretizacion * 3);

		vector<double> nuevaImagen = Simulator1.obtenerImagenPorRayos(vecVacio, 0.1, 4, 1);

		// no tengo que calcular el ECM, después puede que lo haga en octave, veremos
	}
}

void compararECMsImagenes(){
	// Primero 32x32
	cout << "sale 32x32" << endl;

	fstream sal1("exp_nipo/condiion_number_exp/ecms32x32.csv", ios::out);

	sal1 << "ECMon,ECMom" << endl;

	string pathEntradaOctave = "exp_nipo/condition_number_exp/out_images/32x32/";
	string pathEntradaReal = "exp_nipo/condition_number_exp/csvs_in/32x32/";
	for(int i = 0; i < 15; i++){
		string pathImagenOriginalSinCsv = pathEntradaReal + to_string(i);
		vector<int> imagenOriginal = csvToVector(pathImagenOriginalSinCsv);
		vector<double> imagenOriginalDouble = vectorIntToVectorDouble(imagenOriginal);
		vector<double> origNormalizada = normalizar(imagenOriginalDouble);

		string pathImagenOctaveNormalSinCsv = pathEntradaOctave + to_string(i) + "_normal";
		vector<int> imagenOctaveNormal = csvToVector(pathImagenOctaveNormalSinCsv);
		vector<double> imagenOctaveNormalDouble = vectorIntToVectorDouble(imagenOctaveNormal);
		vector<double> octaveNormalNormalizada = normalizar(imagenOctaveNormalDouble);

		string pathImagenOctaveModifSinCsv = pathEntradaOctave + to_string(i) + "_modif";
		vector<int> imagenOctaveModif = csvToVector(pathImagenOctaveModifSinCsv);
		vector<double> imagenOctaveModifDouble = vectorIntToVectorDouble(imagenOctaveModif);
		vector<double> octaveModifNormalizada = normalizar(imagenOctaveModifDouble);

		double ecm1 = ECM(origNormalizada, octaveNormalNormalizada);
		double ecm2 = ECM(origNormalizada, octaveModifNormalizada);

		sal1 << ecm1 << "," << ecm2 << endl;
	}

	// Ahora 64x64
	cout << "sale 64x64" << endl;

	fstream sal2("exp_nipo/condiion_number_exp/ecms64x64.csv", ios::out);

	sal2 << "ECMon,ECMom" << endl;

	pathEntradaOctave = "exp_nipo/condition_number_exp/out_images/64x64/";
	pathEntradaReal = "exp_nipo/condition_number_exp/csvs_in/64x64/";
	for(int i = 0; i < 15; i++){
		string pathImagenOriginalSinCsv = pathEntradaReal + to_string(i);
		vector<int> imagenOriginal = csvToVector(pathImagenOriginalSinCsv);
		vector<double> imagenOriginalDouble = vectorIntToVectorDouble(imagenOriginal);
		vector<double> origNormalizada = normalizar(imagenOriginalDouble);

		string pathImagenOctaveNormalSinCsv = pathEntradaOctave + to_string(i) + "_normal";
		vector<int> imagenOctaveNormal = csvToVector(pathImagenOctaveNormalSinCsv);
		vector<double> imagenOctaveNormalDouble = vectorIntToVectorDouble(imagenOctaveNormal);
		vector<double> octaveNormalNormalizada = normalizar(imagenOctaveNormalDouble);

		string pathImagenOctaveModifSinCsv = pathEntradaOctave + to_string(i) + "_modif";
		vector<int> imagenOctaveModif = csvToVector(pathImagenOctaveModifSinCsv);
		vector<double> imagenOctaveModifDouble = vectorIntToVectorDouble(imagenOctaveModif);
		vector<double> octaveModifNormalizada = normalizar(imagenOctaveModifDouble);

		double ecm1 = ECM(origNormalizada, octaveNormalNormalizada);
		double ecm2 = ECM(origNormalizada, octaveModifNormalizada);

		sal2 << ecm1 << "," << ecm2 << endl;
	}
}



// void testAsd(){
// 	string path = "exp_nipo/test.csv";
// 	TCSimulator Simulator(path);
// 	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosOpuestos(Simulator.getHeight(), Simulator.getWidth(), 10);
// 	Simulator.generarRayos(20, rayosTomo1);
// 	Image* nuevaImagen = Simulator.regenerarImagen();
// 	nuevaImagen->SaveImage("exp_nipo/in/testCM.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);
// 	delete nuevaImagen;
// }

void testAsf(){
	string path = "exp_nipo/out/testCM.csv";
	TCSimulator Simulator(path, "exp_nipo/out/regenerada.csv");
	// Simulator.imageMatrix->convertToCSV("exp_nipo/tomo");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 21);
	// cout << rayosTomo1.size() << endl;
	vector<pair<pair<double, double>, pair<double, double> > > asd;
	Simulator.generarRayos(62, rayosTomo1);
	Image nuevaImagen = Simulator.regenerarImagenConDiscretizacion(1);
	// nuevaImagen->SaveImage("exp_nipo/in/juan.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);
}

void testTomo(){
	string path = "exp_nipo/in/resize_tomo1.csv";
	TCSimulator Simulator(path, "exp_nipo/out/resize_tomo1_out2_32x32.csv");
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo1 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 100);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo2 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 100);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo3 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 100);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo4 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 100);
	vector<pair<pair<double, double>, pair<double, double> > > rayosTomo5 = generadorRayosPuntoFijoIzq(Simulator.getHeight(), Simulator.getWidth(), 100);
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo2.begin(), rayosTomo2.end());
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo3.begin(), rayosTomo3.end());
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo4.begin(), rayosTomo4.end());
	rayosTomo1.insert(rayosTomo1.end(), rayosTomo5.begin(), rayosTomo5.end());
	vector<pair<pair<double, double>, pair<double, double> > > asd(3000);
	vector<double> nuevaImagen = Simulator.obtenerImagenPorRayos(asd, 0, 4, 1);
	// vector<double> carlos = csvToVector(32, 32, "resize_tomo1_out2_32x32");
	// mostrarVector(carlos);
}


int main(){
	srand(time(NULL));
	// iterateCSVs();
	// vector<pair<pair<double, double>, pair<double, double> > > carlos = generadorRayosPuntoFijo(5, 5, 5, 0);
	// mostrarVectorPairPairDoubleNipo(carlos);
	// cout << carlos.size() << endl;
	// vector<pair<pair<double, double>, pair<double, double> > > cruzados = generadorRayosCruzadosModif(32, 32, 31);
	// generarCSVVectorPairPair(cruzados, "testeoCruzadosModif");
	// mostrarVectorPairPairDoubleNipo(cruzados);
	// vector<pair<pair<double, double>, pair<double, double> > > opuestos = generadorRayosOpuestosModif(32, 32, 31);
	// generarCSVVectorPairPair(opuestos, "testeoOpuestosModif");
	// mostrarVectorPairPairDoubleNipo(opuestos);
	// cout << fRand(0.5, 5.3) << endl;
	// testAsd();
	// testAsf();
	// verSiOpuestosBien();
	// testTomo();
	// vector<double> carlos =  csvToVector("asd");
	// mostrarVector(carlos);
	// testRayosOpuestosTomosCatedraPosta(20, 4);
	// testRayosCruzadosTomosCatedraPosta(20, 4);
	// testRayosFijosTomosCatedraPosta(20, 4);
	// testRayosAleatoriosPosta(90, 4);
	// testRayosOpuestosTomosCatedraPosta(0, 4);
	// testRayosCruzadosTomosCatedraPosta(0, 4);
	// testRayosFijosTomosCatedraPosta(0, 4);
	// testRayosAleatoriosPosta(0, 4);
	// string guardarRayos = "exp_nipo/rayos_out/rayo";
	// string final = guardarRayos + to_string(2);
	// cout << final << endl;
	// testRayosOpuestosTomosCatedraRayosYCsv(20, 4);
	// testRayosCruzadosTomosCatedraRayosYCsv(20, 4);
	// testRayosFijosTomosCatedraRayosYCsv(20, 4);
	// testRayosAleatoriosRayosYCsv(20, 4);
	exportAtAyAtb(15);
	return 0;
}