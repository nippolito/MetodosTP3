#include "Image.cpp"
#include "TCSimulator.h"
#include <fstream>
#include <vector>
#include <random>
#include "matrizRala.h"
#include <iostream>

//Media pila chicos y usen esta funcion con un orden que divida tanto alto y ancho, si no les cabe 
void discretizarMatrizDireccionesEnOrdenDe(Rala& original, Rala& discretizada, int ordenDeMagnitud){
	if (original.n != discretizada.n * ordenDeMagnitud || original.m != discretizada.m * ordenDeMagnitud)
	{
		cout << "Discretizacion con orden de magnitud o tamaño de matriz resultado incorrectos" << endl;
		return;
	}

	for (int i = 0; i < original.n; ++i)
	{
		int posFilaEnDiscretizacion = floor(i/ordenDeMagnitud);
		
		// map<int,double>::iterator distResultado = discretizada.conex[posFilaEnDiscretizacion].find(0);
		// map<int,double>::iterator distResultadoB = distResultado;
		
		map<int,double>::iterator it = original.conex[i].begin();
		for(; it != original.conex[i].end(); it++){
			cout << "hay elemento en " << i << " - " << it->first << endl;	

			int posCol = it->first;
			int posColEnDiscretizacion = floor(posCol / ordenDeMagnitud);

			map<int,double>::iterator distDiscretizacion = discretizada.conex[posFilaEnDiscretizacion].find(posColEnDiscretizacion);
			if (distDiscretizacion == discretizada.conex[posFilaEnDiscretizacion].end())
				discretizada.conex[posFilaEnDiscretizacion].insert(pair<int,double>(posColEnDiscretizacion, 1));
			else
				distDiscretizacion->second += 1;
		}
	}

}

void probarDiscretizacion(){
	int n = 4;

	Rala r = Rala(n,n);
	insertarElemento(r,0,0,1);
	insertarElemento(r,0,1,2);
	insertarElemento(r,0,2,3);
	insertarElemento(r,0,3,4);


	insertarElemento(r,1,1,1);
	insertarElemento(r,1,3,2);


	insertarElemento(r,2,0,3);
	insertarElemento(r,2,1,6);
	insertarElemento(r,2,2,9);
	

	insertarElemento(r,3,0,4);
	insertarElemento(r,3,1,1);
	insertarElemento(r,3,3,1);

	int ordMagnitud = 2;

	mostrarRala(&r);
	Rala rD = Rala(n/ordMagnitud,n/ordMagnitud);
	discretizarMatrizDireccionesEnOrdenDe(r, rD, ordMagnitud);
	mostrarRala(&rD);
}

void probarCM(){

	//1
	Rala r1 = Rala(3,6);
	insertarElemento(r1,0,0,4);
	insertarElemento(r1,0,1,2);
	insertarElemento(r1,0,2,1);
	insertarElemento(r1,0,3,7);


	insertarElemento(r1,1,1,1);
	insertarElemento(r1,1,3,2);


	insertarElemento(r1,2,2,3);
	insertarElemento(r1,2,3,6);
	insertarElemento(r1,2,5,9);

	generarCSV(r1, "4_A");
	vector<double> b1 = vector<double>();
	b1.push_back(4);
	b1.push_back(2);
	b1.push_back(6);
	generarCSVVector(b1, "4_b");

	vector<double> x1 = resolverCM(r1, b1);
	generarCSVVector(x1, "4_x");

	vector<double> xOctave = vector<double>();
	xOctave.push_back(-0.540867810292636);
	xOctave.push_back(0.5105953582240164);
	xOctave.push_back(-0.07063572149343955);
	xOctave.push_back(0.7447023208879929);
	xOctave.push_back(0);
	xOctave.push_back(0.1937436932391515);

	vector<double> R1x1 = vector<double>(3);
	multiplicacionPorVector(r1,x1,R1x1);
	vector<double> R1xOctave = vector<double>(3);
	multiplicacionPorVector(r1,xOctave,R1xOctave);
	mostrarVector(R1x1);
	mostrarVector(R1xOctave);
	mostrarVector(b1);
}


void probarCMMasFilasQCol(){

	//1
	Rala r1 = Rala(6,3);
	insertarElemento(r1,0,0,4);
	insertarElemento(r1,0,1,2);
	insertarElemento(r1,0,2,1);


	insertarElemento(r1,1,1,1);
	insertarElemento(r1,1,0,2);


	insertarElemento(r1,2,1,3);
	insertarElemento(r1,2,2,6);


	insertarElemento(r1,3,0,4);
	insertarElemento(r1,3,1,2);
	insertarElemento(r1,3,2,1);


	insertarElemento(r1,4,1,1);
	insertarElemento(r1,4,0,2);


	insertarElemento(r1,5,1,3);
	generarCSV(r1, "4_A");
	vector<double> b1 = vector<double>();
	b1.push_back(4);
	b1.push_back(2);
	b1.push_back(6);
	b1.push_back(6);
	b1.push_back(6);
	b1.push_back(6);
	generarCSVVector(b1, "4_b");

	vector<double> x1 = resolverCM(r1, b1);
	generarCSVVector(x1, "4_x");


	vector<double> xOctave = vector<double>();
	xOctave.push_back(0.3804347826086951);
	xOctave.push_back(2.065217391304349);
	xOctave.push_back(-0.06521739130434838);

	vector<double> R1x1 = vector<double>(6);
	multiplicacionPorVector(r1,x1,R1x1);
	vector<double> R1xOctave = vector<double>(6);
	multiplicacionPorVector(r1,xOctave,R1xOctave);
	mostrarVector(R1x1);
	mostrarVector(R1xOctave);
	mostrarVector(b1);
}
int main(){
	//probarDiscretizacion();
	//probarCM();
	probarCMMasFilasQCol();
	return 0;
}