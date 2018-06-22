#ifndef __RALA_H__
#define __RALA_H__

#include <iostream>
#include <fstream>
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
	Rala(int filas, int columnas ){
		n = filas;
		m = columnas;
		for(int i = 0 ; i < n ; i ++){
			conex.push_back(map<int,double> ());
		}
	}

	int n; //Cantidad de filas
	int m; //Cant de columnas, o longitud de filas.
	vector< map<int, double> > conex; // lista de adyacencia. 

};


//--------------------------------------------------------FUNCIONES PARA MOSTRAR MATRICES

void mostrarVector(vector<double> x){
	cout << "[";
	for(int k = 0 ; k < x.size(); k++){
		cout << x[k] << ", " ;
	}
	cout << "]" << endl;
}

void mostrarArreglo(double* vec, int n){
	cout << "[" ;
	for (int i = 0; i < n; ++i)
	{
		cout << vec[i] << ", ";
	}
	cout << "]" << endl;
}

void mostrarVectorPair(map<int,double>* filas, int m){
	// cout << "longitud de vec: " << vec.size() << endl;
	cout << "[";
	for(int i =  0 ; i < m ; i ++){
		map<int,double>::iterator it = filas -> find(i);
		string comaOrEnd = i == m-1 ? "" : ", "; 
		if(it != filas->end()){
			cout <<  it -> second << comaOrEnd;
		}else{
			cout <<"0" << comaOrEnd;
		}
	}
	cout << "]" << endl;
}

void mostrarVectorPair2(map<int,double>* filas, int m){
	// cout << "longitud de vec: " << vec.size() << endl;
	cout << "[";
	for(int i =  0 ; i < m ; i ++){
		map<int,double>::iterator it = filas -> find(i);
		string comaOrEnd = i == m-1 ? "" : ", "; 
		if(it != filas->end()){
			cout << "(" << it->first << "," <<it -> second << ")"<< comaOrEnd;
		}else{
			//cout <<"0" << comaOrEnd;
		}
	}
	cout << "]" << endl;
}

void mostrarRala(Rala* matriz){
	for(int link = 0; link < matriz->n; link++){
		mostrarVectorPair(&matriz->conex[link], matriz->m);
	}
}

void mostrarRala2(Rala* matriz){
	for(int link = 0; link < matriz->n; link++){
		mostrarVectorPair2(&matriz->conex[link], matriz->m);
	}
}



//OPERACIONES


// inserta elemento en la matriz A.
void insertarElemento(Rala& A, int fila, int columna, double valor ){
	//Nuevo: Si se quiere insertar un elemento que excede la longitud de la fila, o cant. de columnas, explota.
	if(A.m <= columna ||  A.n <= fila) { 
		cout << "Error de dimensiones. La posicon: (" << fila<< ", " << columna << ")" << " no esta permitida" << endl;
		return;
	}
	
	map<int,double>::iterator it = A.conex[fila].find(columna);
	if( it == A.conex[fila].end() ){
		A.conex[fila].insert(pair<int,double>(columna,valor));			
	}else{
		it -> second = valor;
	}
}


// crea en At la matriz transpuesta de A
// PRECONDICION: A y At aunque vacias, deben tener las dimensiones correctas.
void createTranspose(Rala& A, Rala& At){
	cout<< "CREATE TRASNSPOSE --> " << endl;
	int n = A.n;
	for(int i = 0; i < n ; i ++){
		for(map<int,double>::iterator it = A.conex[i].begin() ; it != (A.conex[i]).end(); it ++){
			insertarElemento(At, it->first, i, it -> second);
		}
	}
}

// crea matriz identidad necesaria para el cálculo del pageRank
//Ahora puede ser la identidad no cuadrada
Rala CrearIdentidad(int n, int m ){
	cout<< "CREATE IDENTIDAD--> " << endl;
	Rala res = Rala(n,m);
	int mayor = max(n,m);
	for(int i = 0 ; i < mayor; i++){
		insertarElemento(res, i, i, 1 );
	}
	return res;
}





// suma las matrices A y B y devuelve la suma en C
void sumaMatricial(Rala& A, Rala& B, Rala& C){
	cout<< "SUMA MATRICIAL --> " << endl;
	if(A.n != B.n || A.m != B.m){
		cout<< "Error de dimensiones al sumar matrices no compatibles!" << endl;
		return;
	}

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

int primeraFilaSinUnCeroEnLaCol(Rala& A, int col){
	int n = A.n;
	for(int i = 0 ; i < n; i ++ ){
		if(A.conex[i].begin()->first == col){
			return i ;
		}
	}
	return -1 ;
}

void swapearPivotConCol(Rala& A, vector<double> & conjunta, int pivot, int col){
	map<int,double> filaCol = A.conex[col];
	A.conex[col] = A.conex[pivot];
	A.conex[pivot] = filaCol;

	double conjCol = conjunta[col];
	conjunta[col]=conjunta[pivot];
	conjunta[pivot]=conjCol;
}

void eliminacionGaussiana(Rala & A, vector<double> & conjunta){
	cout << "ELIMINACINO GAUSSIANA -->" << endl;
	int n = A.n ;
	long long int entra = 0;
	long long int noentra = 0;
	for(int col = 0  ; col < n ; col ++){
		//cout << "voy por la columna: " << col <<endl;
		int filaPivot = primeraFilaSinUnCeroEnLaCol(A,col);
		//si la columna no son todos ceros entonces...
		if(filaPivot != -1){
			swapearPivotConCol(A,conjunta, filaPivot,col);  //pongo una col con un valor diferente de cero en la fila que itero
			map<int,double> pivot = A.conex[col];

			for(int j = col+1; j < A.n ; j++){
				if(A.conex[j].begin() != A.conex[j].end() && A.conex[j].begin() -> first == col){ // si la columna de abajo no tiene un cero en col entonces la redusco
					reduceRowFromPivot(A.conex[j],pivot, j, col ,n, conjunta);
				}
			}
		}
	}
}

// resuelve ecuaciones lineales y deja en res el resultado
// A tiene que ser cuadrada
void solveLinearEquations(Rala& A, vector<double> & conjunta, vector<double> & res){
	int n = A.n;

	//cout<<"MATRIZ ANTES DE EG:" <<endl;
	//mostrarRala(&A);
	//cout << "LA CONJUNTA ANTES DE LA EG" << endl;
	//mostrarVector(conjunta);
	eliminacionGaussiana(A, conjunta);
	//cout<<"\nMATRIZ DESPUES DE EG:" << endl;
	//mostrarRala(&A);
	//cout << "\nLA CONJUNTA DESPUES DE EG" << endl;
	//mostrarVector(conjunta);

	cout << "pasa eliminacion gaussiana" << endl;

	for(int i = n-1; i >= 0 ; i --){
		double ac = 0 ;
		for(int j = n-1 ; j > i ; j --){
			map<int,double>::iterator it2  = (A.conex[i]).find(j);
			if(it2 != (A.conex[i]).end() ){
				ac += (res[j] * (it2 -> second));	
			}
		}
		if((A.conex[i]).find(i) != A.conex[i].end()){
			res[i] = (conjunta[i] - ac )/ (A.conex[i]).find(i)->second;	
		}
		else{
			ac = (conjunta[i] - ac );
			if(abs(ac) > 0.000000001){
				cout << "\n\n -------- " << endl;
				cout << "el sistema no tiene solucion" << endl;
				cout << "La matriz es:" << endl;
				//mostrarRala(&A);
				cout << "\nY la conjunta es " << endl;
				//mostrarVector(conjunta);
				return;
			}
			res[i]=1;
		}
		
	} 
	//cout << "LA RESPUESTA FINAL: " << endl;
	//mostrarVector(res);
}

//NUEVO

//A, B: MATRICES A MULTIPLICAR
//C: MATRIZ RESULTADO DEBE TENER LAS DIMENSIONES CORRECTAS (aunque como es rala, basta con que C.n sea igual que A.n)
void multiplicacionMatricial(Rala& A, Rala& B, Rala& C){
	cout<< "MULTIPLICACION MATRICIAL --> " << endl;
	int nA = A.n;
	if(A.m != B.n || A.n != C.n || B.m != C.m){
		
		cout << "Error al multiplicar matrices no cuadradas! La matriz de salida no tiene la misma cantidad de filas que A"<< endl;
		return;
	}

	Rala transp = Rala(B.m, B.n);
	createTranspose(B, transp);

	//Ahora transp tiene:
	//transp.conex.size = cantidad de columnas
	int maxColumnaB = transp.m;
	cout<< "MULTIPLICANDO MATRICES --> " << endl;
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


//Dado que al crear una matriz rala, esta no esta "vacia" sino que posee un map por cada fila vacio,
//"Añadir filas" no es mas que reemplazar la fila existente por otra que se desea crear. 
//Usar este metodo para contruir y luego rellenar la matriz A solucion final.
void reemplazarFila(Rala& A,int posicion, map<int,double>& fila){
	A.conex[posicion] = fila;
}

	

//Toma una matriz rala, donde solo hay 1 en los pixels por donde pasa el rayo. En el resto hay 0.
//Lo convierte en una fila de la matriz rala de la solucion final. (Insertar en la matriz final a mano)
map<int, double> convertirRayoEnFila(Rala& A){
	map<int,double> res;

	int numeroDePixel = 0;
	int nfilas = A.n;
	int mcolumnas = A.m;

	int pxl_size = 3;
	for (int i = 0; i < nfilas; i++)
	{
		map<int,double>::iterator it = A.conex[i].begin();
		for(; it != A.conex[i].end(); it++){
			res.insert(pair<int,double>(i*A.m + it->first, 1));
		}
	}

	return res;
}

void generarCSV(Rala&A){
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


//Resolver CM: AtAx = Atb;
vector<double> resolverCM(Rala& A, vector<double>& b){
	vector<double> x(A.m, 0);
	vector<double> Atb (A.m, 0);
	Rala At(A.m, A.n);
	Rala AtA(A.m, A.m);
	
	createTranspose(A, At);
	cout <<"bk1" << endl;
	multiplicacionPorVector(At, b, Atb);
	cout <<"bk2" << endl;
	multiplicacionMatricial(At, A, AtA);
	cout <<"bk3" << endl;
	solveLinearEquations(AtA, Atb, x);
	cout <<"bk5" << endl;
	return x;
}



#endif