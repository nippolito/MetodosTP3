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


void pruebaPLU(){
	int n = 4;

	//[1,2,3,4]
	//[0,1,0,2]
	//[3,6,15,0]
	//[4,1,0,1]

	Rala r = Rala(n,n);
	insertarElemento(r,0,0,1);
	insertarElemento(r,0,1,2);
	insertarElemento(r,0,2,3);
	insertarElemento(r,0,3,4);


	insertarElemento(r,1,0,0);
	insertarElemento(r,1,1,1);
	insertarElemento(r,1,2,0);
	insertarElemento(r,1,3,2);


	insertarElemento(r,2,0,3);
	insertarElemento(r,2,1,6);
	insertarElemento(r,2,2,9);
	insertarElemento(r,2,3,0);


	insertarElemento(r,3,0,4);
	insertarElemento(r,3,1,1);
	insertarElemento(r,3,2,0);
	insertarElemento(r,3,3,1);

	std::vector<double> conjunta;
	conjunta.push_back(1);
	conjunta.push_back(1);
	conjunta.push_back(1);
	conjunta.push_back(1);

	cout<<"MATRIZ ANTES DE EG:" <<endl;
	mostrarRala(&r);
	eliminacionGaussiana(r,conjunta);
	cout << "" << endl;
	cout<<"MATRIZ DESPUES DE EG:" << endl;
	mostrarRala(&r);

}


void pruebaSolveLinearEquation(){
	int n = 4;

	//[1,2,3,4]
	//[0,1,0,2]
	//[3,6,15,0]
	//[4,1,0,1]

	Rala r = Rala(n,n);
	insertarElemento(r,0,0,1);
	insertarElemento(r,0,1,2);
	insertarElemento(r,0,2,3);
	insertarElemento(r,0,3,4);


	insertarElemento(r,1,0,0);
	insertarElemento(r,1,1,1);
	insertarElemento(r,1,2,0);
	insertarElemento(r,1,3,2);


	insertarElemento(r,2,0,3);
	insertarElemento(r,2,1,6);
	insertarElemento(r,2,2,9);
	insertarElemento(r,2,3,0);


	insertarElemento(r,3,0,4);
	insertarElemento(r,3,1,1);
	insertarElemento(r,3,2,0);
	insertarElemento(r,3,3,1);

	std::vector<double> conjunta;
	conjunta.push_back(1);
	conjunta.push_back(1);
	conjunta.push_back(1);
	conjunta.push_back(1);

	vector<double> res (n,0);


	solveLinearEquations(r,conjunta,res);

}

void pruebaSolveLinearEquationWhenShitIsOnFire(){
	int n = 4;

	//[1,2,3,4]
	//[0,1,0,2]
	//[0,0,0,4]
	//[0,0,0,3]

	Rala r = Rala(n,n);
	insertarElemento(r,0,0,1);
	insertarElemento(r,0,1,2);
	insertarElemento(r,0,2,3);
	insertarElemento(r,0,3,4);


	insertarElemento(r,1,0,0);
	insertarElemento(r,1,1,1);
	insertarElemento(r,1,2,0);
	insertarElemento(r,1,3,2);


	insertarElemento(r,2,0,0);
	insertarElemento(r,2,1,0);
	insertarElemento(r,2,2,0);
	insertarElemento(r,2,3,4);


	insertarElemento(r,3,0,0);
	insertarElemento(r,3,1,0);
	insertarElemento(r,3,2,0);
	insertarElemento(r,3,3,3);

	std::vector<double> conjunta;
	conjunta.push_back(8+4+3+1);
	conjunta.push_back(6);
	conjunta.push_back(8);
	conjunta.push_back(6);

	vector<double> res (n,0);


	solveLinearEquations(r,conjunta,res);

}




int main(){
	pruebaSolveLinearEquationWhenShitIsOnFire();
	//pruebaSolveLinearEquation();

	return 0;
}












