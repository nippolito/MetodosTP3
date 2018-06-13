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
	Rala A = Rala(3);

	Rala B = Rala(3);

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

	Rala C = Rala(A.n);
	multiplicacionMatricialNoCuadrada(A, B, C);
	cout << endl;
	mostrarRala(&C);	
}



int main(){
	Test1ParaMult();
	return 1;
}