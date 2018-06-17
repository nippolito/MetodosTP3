#include "Image.cpp"
//#include "TCSimulator.cpp"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"


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
	Rala A = Rala(3,3);

	insertarElemento(A, 0, 0, 1);
	insertarElemento(A, 1, 1, 1);
	insertarElemento(A, 2, 2, 1);
	
	vector<double> b;
	b.push_back(4);
	b.push_back(5);
	b.push_back(1);

	vector<double> res = resolverCM(A, b);

	for (int i = 0; i < 3; ++i)
	{
		cout << res[i] << endl;
	}
}


int main(){
	//Test1ParaMult();
	//TestParaAplanar();
	TestParaCM();
	return 1;
}