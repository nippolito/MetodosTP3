#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility>
#include <map>
#include <cmath>
#include <stdio.h> 
#include <float.h>

using namespace std;

class Rala{
public:
	Rala(int size ){
		n = size;

		for(int i = 0 ; i < n ; i ++){
			conex.push_back(map<int,double> ());
		}
	}

	int n;
	vector< map<int, double> > conex; // lista de adyacencia. 

};


//--------------------------------------------------------FUNCIONES PARA MOSTRAR MATRICES

void mostrarVectorPair(map<int,double>* m, int n){
	// cout << "longitud de vec: " << vec.size() << endl;
	cout << "[";
	for(int i =  0 ; i < n ; i ++){
		map<int,double>::iterator it = m -> find(i);
		string comaOrEnd = i == n-1 ? "" : ", "; 
		if(it != m->end()){
			cout <<  it -> second << comaOrEnd;
		}else{
			cout <<"0" << comaOrEnd;
		}
	}
	cout << "]" << endl;
}

void mostrarRala(Rala* matriz){
	for(int link = 0; link < matriz->n; link++){
		mostrarVectorPair(&matriz->conex[link], matriz->n);
	}
}



//OPERACIONES


// inserta elemento en la matriz A.
void insertarElemento(Rala& A, int fila, int columna, double valor ){
	map<int,double>::iterator it = A.conex[fila].find(columna);
	if( it == A.conex[fila].end() ){
		A.conex[fila].insert(pair<int,double>(columna,valor));			
	}else{
		it -> second = valor;
	}
}

// devuelve el grado de la página j (o sea, la cantidad de elems en la columna j, o #linksSalientes)
int gradoSalida(struct Rala& A, int j){
	int res = 0;
	int n = A.n;
	for(int i = 0; i < n; i++){
		if( A.conex[i].find(j) != A.conex[i].end()){
			res++;
		}
	}
	return res;
}

// crea en At la matriz transpuesta de A
void createTranspose(Rala& A, Rala& At){
	int n = A.n;
	for(int i = 0; i < n ; i ++){
		for(map<int,double>::iterator it = A.conex[i].begin() ; it != (A.conex[i]).end(); it ++){
			insertarElemento(At, it->first, i, it -> second);
		}
	}
}

// crea matriz identidad necesaria para el cálculo del pageRank
Rala CrearIdentidad(int n ){
	Rala res = Rala(n);
	for(int i = 0 ; i < n; i++){
		insertarElemento(res, i, i, 1 );
	}
	return res;
}

// genera el vector e que es necesario para el cálculo del pageRank
vector<double> generarVectorE(int n){
	vector <double> result(n, 1.0);
	return result;
}

// A tiene que ser matriz nula. W matriz de conectividad.
// Devuelve la diagonal en A
int generarMatrizDiagonalD(Rala & A, Rala & W){
	if (A.n != W.n){ return -1;}
	int n = W.n;

		for (int fila = 0; fila < n; ++fila)
		{
			int grado = gradoSalida(W, fila);
			if(grado != 0){
				
				double valor = 1.0/grado;
				insertarElemento(A, fila, fila, valor);
			}

		}

		return 1;	
}

// suma las matrices A y B y devuelve la suma en C
void sumaMatricial(Rala& A, Rala& B, Rala& C){ 
	int n = A.n;
	for(int i = 0; i < n; i++){
		map<int, double> filA = A.conex[i];
		map<int, double> filB = B.conex[i];

		map<int, double>::iterator itA = filA.begin();
		map<int, double>::iterator itB = filB.begin();
		

		while(itA != filA.end() || itB != filB.end()){
			if( itB == filB.end()  ||  ((itA -> first < itB -> first) && itA != filA.end()) ){
				insertarElemento(C, i, itA->first, itA->second);
				itA ++;
			}
			else if( itA == filA.end() || ((itA -> first > itB -> first) && itB != filB.end()) ){
				insertarElemento(C, i, itB->first, itB->second);
				itB ++;
			}
			else{
				insertarElemento(C, i, itA->first, itA->second + itB -> second);
				itA ++;
				itB ++;
			}
		}
	}
}

// auxiliar para la multiplicación matricial
// utilizada para obtener el elemento C_filAcolB de la multiplicación entre A y B
double multiplicarFilas(map<int,double>& fila, map<int,double>& col){
	double ac = 0;
	map<int, double>::iterator itF = fila.begin();
	map<int, double>::iterator itC = col.begin();

	while(itF != fila.end() && itC != col.end()){
		if(itF -> first < itC ->first) itF++;
		else if(itC -> first < itF->first) itC ++;
		else{
			ac += itF->second * itC -> second;
			itC++;
			itF++;
		}
	}

	return ac;
}

// multiplica las matrices A y B. Devuelve la multiplicación en C
void multiplicacionMatricial(Rala& A, Rala& B, Rala& C){
	int n = A.n;
	Rala transp = Rala(n);
	createTranspose(B, transp);
	for(int i = 0; i < n; i++){
		for(int j = 0 ; j < n ; j ++){
			map<int,double> filA = A.conex[i];
			map<int,double> colB = transp.conex[j];
			double multRes = multiplicarFilas(filA, colB);
			if(fabs(multRes) > 0){
				insertarElemento(C,i,j,multRes);
			}
		}
	}
}

// A = A*valor
// modifica A
void multiplicacionPorEscalar(Rala& A, double valor){
	for (int i = 0; i < A.conex.size(); i++){
		for(map<int,double>::iterator it = (A.conex[i]).begin(); it != (A.conex[i]).end(); it++){
			it -> second *= valor;
		}
	}
}

// Ax = Y
// Modifica vector res con el resultado de Ax
void multiplicacionPorVector(Rala& A, vector<double>& vecArg, vector<double>& vecRes){
	for (int i = 0; i < A.n; i++){
		map<int,double>::iterator itRow = A.conex[i].begin();
		double sumaFilaColumna = 0.0;
		for (; itRow != A.conex[i].end() ; itRow++)
		{
			sumaFilaColumna += itRow->second * vecArg[itRow->first];
		}
		vecRes[i] = sumaFilaColumna;
	}
}

void reduceRowFromPivot(map<int,double>& row, map<int,double>& pivot, int fila, int col, int n, vector<double> & conjunta){
	map<int,double>::iterator itPivot = pivot.find(col);
	map<int,double>::iterator itRow = row.find(col);
	double pivotBase = itPivot->second;
	double rowBase = itRow->second;
	double coeficiente = rowBase / pivotBase;

	// forzar la primer conversion a 0

	map<int,double>::iterator itAux = itRow;
	itAux ++;
	row.erase(itRow->first);
	itRow = itAux;
	itPivot ++;
	
	// actualizo el vector resultado
							
	conjunta[fila] -=  conjunta[col] * coeficiente; 

	while(itPivot != pivot.end() ){
		// recorro la fila del pivote pues si hay un cero en una columna, no hay que hacer nada
		if( itRow == row.end()){
			// si llegaste al final de la fila que estabas modificando, entonces hubo varios ceros antes
			// que ahora vas a tener que modificar
			for(;itPivot != pivot.end(); itPivot ++){
				row.insert(pair<int,double>(itPivot->first, -1 * (itPivot->second) * coeficiente));
			}
		}
		else{
			if(itRow -> first == itPivot -> first){
				// si están ambos en la misma col, realizo los cálculos
				std::map<int, double>::iterator itAux = itRow;
				itAux ++;
				if(fabs((itRow -> second) - coeficiente * (itPivot -> second)) > DBL_EPSILON){
					// si la resta no se vuelve cero, modifico el valor
					itRow -> second = (itRow -> second) - coeficiente * (itPivot -> second );

				}else{
					// si la resta dio cero, tengo que eliminar el elemento
					row.erase(itRow);
				}
				itPivot ++;
				itRow = itAux; 
			}
			else if (itRow -> first > itPivot -> first) {
				// si el iterador de la fila estaba más avanzado que el pivot, me saltié por lo menos un cero de la fila y necesito hacer el cálculo
				row.insert(pair<int,double>(itPivot->first, -1 * (itPivot->second) * coeficiente));
				itPivot ++;
			}
			else if (itRow -> first < itPivot -> first) {
				// si el iterador de la fila estaba menos avanzado que el pivot, lo avanzo (pues significa que en esa columna el pivot tiene un 0)
				itRow ++;
			}
		}
	}
}

void eliminacionGaussiana(Rala & A, vector<double> & conjunta){
	int n = A.n ;
	long long int entra = 0;
	long long int noentra = 0;
	for(int col = 0  ; col < n ; col ++){	
		map<int,double> pivot = A.conex[col];

		for(int j = col+1; j < A.n ; j++){
			if(A.conex[j].begin() -> first == col ){
				// hago resta de filas
				reduceRowFromPivot(A.conex[j],pivot, j, col ,n, conjunta);
			}
		}
	}
}

// resuelve ecuaciones lineales y deja en res el resultado
void solveLinearEquations(Rala& A, vector<double> & conjunta, vector<double> & res , int n ){
	eliminacionGaussiana(A, conjunta);
	
	for(int i = n-1; i >= 0 ; i --){
		double ac = 0 ;
		for(int j = n-1 ; j > i ; j --){
			map<int,double>::iterator it2  = (A.conex[i]).find(j);
			if(it2 != (A.conex[i]).end() ){
				ac += (res[j] * (it2 -> second));	
			}
		}
		res[i] = (conjunta[i] - ac )/ (A.conex[i]).find(i)->second;
	} 
}

//NUEVO

//A, B: MATRICES A MULTIPLICAR
//C: MATRIZ RESULTADO DEBE TENER LAS DIMENSIONES CORRECTAS (aunque como es rala, basta con que C.n sea igual que A.n)
void multiplicacionMatricialNoCuadrada(Rala& A, Rala& B, Rala& C){
	int nA = A.n;
	int nC = C.n;
	if (nA != nC){
		
		cout << "Error al multiplicar matrices no cuadradas! La matriz de salida no tiene la misma cantidad de filas que A"<< endl;
		return;
	}

	Rala transp = Rala(nA);
	createTranspose(B, transp);

	//Ahora transp tiene:
	//transp.conex.size = cantidad de columnas
	int maxColumnaB = transp.conex.size();

	//Itero por las i filas de A
	for(int i = 0; i < nA; i++){
		for(int j = 0 ; j < maxColumnaB ; j ++){
			map<int,double> filA = A.conex[i];
			map<int,double> colB = transp.conex[j];
			double multRes = multiplicarFilas(filA, colB);
			if(fabs(multRes) > 0){
				insertarElemento(C,i,j,multRes);
			}
		}
	}
}


	
//PAGERANK TP1 (EN DESUSO)

// resuelve el PageRank
// entradas: matriz de conectividad W, vector res para la salida (debe tener size n)
/*
void resolverPageRank(Rala& W, vector<double>& res, double p){
	int n = W.n;
	Rala WxDxp = Rala(n);
	Rala MatrizAIgualar = Rala(n);
	Rala I = CrearIdentidad(n);
	Rala D  = Rala(n);
	vector<double> e = generarVectorE(n);	//Creo e 
	
	double prob = p * (-1); //uso -p para poder multiplicar directamente y luego usar sumaMatricial.

	generarMatrizDiagonalD(D, W); //Creo D según la matriz de conectividad W

	multiplicacionMatricial(W, D, WxDxp); // WD => WxDxp
	multiplicacionPorEscalar(WxDxp, prob); // WxDxp = -pWD

	sumaMatricial(I, WxDxp, MatrizAIgualar);		// WxDxp = (I + (-pWD))

	solveLinearEquations(MatrizAIgualar, e, res, n);


	// Normalizo el vector
	double normaUno = 0;
	for(int i = 0; i < n; i++){
		normaUno = normaUno + res[i]; 
	}

	for(int i = 0; i < n; i++){
		res[i] = res[i] / normaUno;
	}	
}
*/



