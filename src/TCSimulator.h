#ifndef __SIMULADOR_H__
#define __SIMULADOR_H__

#include <iostream>
#include <vector>
#include <math.h>
#include "matrizRala.h"
#include <stdlib.h>
#include <algorithm> 

using namespace std;

int red=0;
int green = 1;
int blue = 2;

struct Recta{
	double a;
	double b;
	
	Recta(){}

	Recta(double a2, double b2){
		a = a2;
		b = b2;
	}

	double f(double x){
		return a*x + b;
	}

	void print(){
		cout << "y = " << a << ".x + (" << b <<")" << endl;
	}
};

struct Image{
	int height;
	int width;
	vector<vector<int> > imageBuffer;

	Image(vector<vector<int>> image, int height, int width){
		this->height = height;
		this->width = width;
		this->imageBuffer = image;
	}
	Image(){

	}
};

class TCSimulator
{
public:
	
	//Properties
	Image imageMatrix;
	vector<Rala> rayos;
	vector<double> tiempos;
	vector<double> solucion;
	string savingPath;


	int llenarRenglon(vector<int>& pixeles, string renglon){
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

	 

	TCSimulator(string path, string savingPath){
		this->savingPath = savingPath;
		filebuf fb;
		fb.open (path,std::ios::in);
		std::istream fs (&fb);

	    string s;

	    vector<string> renglones; 
	    int cantDeRenglones = 0 ;
	    int cantElementosPorRenglon = 0 ;

	    while(getline(fs,s)){
	        renglones.push_back(s);
	        cantDeRenglones ++ ;
	    }

	    vector<vector<int> > pixeles;
	    for(int i = 0 ;i < cantDeRenglones; i++){
	    	pixeles.push_back(std::vector<int> ());
	    }
	    for(int i = 0 ;i < cantDeRenglones; i ++){
	    	cantElementosPorRenglon = llenarRenglon(pixeles[i], renglones[i]);
	    }

	    imageMatrix = Image (pixeles, cantDeRenglones, cantElementosPorRenglon);
	    cout << "TAMAÑOS DE IMAGENES" << endl;
	    cout << "alto " << cantDeRenglones << endl;
	    cout << "ancho " <<  cantElementosPorRenglon << endl;
	}

	TCSimulator(){
		cout << "Mira que estas creando un simulador sin imagen.." << endl;
	}

	~TCSimulator(){		
	}

	int getWidth(){
		return imageMatrix.width;
	}

	int getHeight(){
		return imageMatrix.height;
	}




	void createTCRay(pair<double,double> pixel1, pair<double,double> pixel2, Rala& distances){
          //nos aseguramos que el primer pixel tenga un x menor a pixel2
          //los rayos pueden "ir en sentido contrario" pero para la simulacion los trataremos SIEMPRE
          //de izquierda a derecha
          //PRECONDICION OBLIGATORIA: ambos puntos deben estar en los bordes, osea x = 0 o x = ancho o y = 0 o y = alto

          double a = (double) (pixel2.second - pixel1.second) / (double)(pixel2.first - pixel1.first);
          double b = pixel1.second - a * pixel1.first;

          Recta recta = Recta(a,b);
          //recta.print();

          if(a > 0){ // si la pendiente es poisitiva
                  for (int i = 0; i < distances.m; ++i){
                          int j = (int) floor(recta.f(i));
                          if(j < 0) j = 0 ; // esto para cuando la recta empieza desde el piso
                          if(j>distances.n) j = distances.n;

                          double k = recta.f(i+1); // esta bien que este no sea un entero aviso
                          if(k < 0) k = 0; // esto cuando no pasa por ninguna de las dos columnas
                          if(k > distances.n ) k = distances.n ;// esto cuando se va por el techo la recta.

                          for (; j < k; j++){
                                  //cout << i << " " << j << endl;
                                  insertarElemento(distances,j, i,  1);
                          }
                  }
          }
          else if( a < 0){ // si la pendiente es negativa
                  for (int i = 0; i < distances.m; ++i){
                          int j = (int) ceil(recta.f(i));
                          if(j > distances.n) j = distances.n ; // esto para cuando la recta empieza desde el techo
                          if(j < 0) j = 0;

                          double k = recta.f(i+1);
                          if(k > distances.n) k = distances.n; // esto cuando no pasa por ninguna de las dos columnas
                          if(k < 0) k = 0; // esto cuando se va por el piso la recta

                          for (; j > k; j--)
                          {
                                  insertarElemento(distances, j-1, i , 1);
                          }
                          //cout << "\n" << endl;
                  }
          }
          else{
                  cout << "te toco una funcion constante" << endl;
          }
  }

	double tiempoDeRecorrido(Rala& distances){
		double tiempo = 0 ;
		int n = distances.n;
		int m = distances.m;
		int pxl_size = 3;
		for(int i = 0 ; i < n ; i ++){
			map<int,double>::iterator it = distances.conex[i].begin();
			for(; it != distances.conex[i].end(); it ++){
				tiempo += (imageMatrix.imageBuffer[i][it->first]);
			}
		}
		return tiempo;
	}

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
			//	cout << "hay elemento en " << i << " - " << it->first << endl;	

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
	void generarRayos(int cantRayos, vector<pair<pair<double,double>, pair<double,double> > > pixelesPorDondePasar){
		srand (time(NULL));
		int cantRayosDefinidos = pixelesPorDondePasar.size();
		int cantRayosRandom = cantRayos - cantRayosDefinidos; 
		tiempos = std::vector<double> ();

		for(int i = 0 ; i < cantRayosDefinidos; i++){
			rayos.push_back(Rala(getHeight(), getWidth()));
			pair<double,double> pixel1 = pixelesPorDondePasar[i].first;
			pair<double,double> pixel2 = pixelesPorDondePasar[i].second;
			createTCRay(pixel1, pixel2, rayos[i]);

			tiempos.push_back(tiempoDeRecorrido(rayos[i]));
		}

		for(int i = 0 ; i < cantRayosRandom; i++){
			rayos.push_back(Rala(getHeight(), getWidth()));
			pair<double,double> pixel1;
			pair<double,double> pixel2;
			createTwoRandomPoints(getHeight(), getWidth(), pixel1, pixel2);
			createTCRay(pixel1, pixel2, rayos[i]);

			tiempos.push_back(tiempoDeRecorrido(rayos[i]));
		}
	}

	vector<vector<int> > desAplanarImagen(std::vector<double>& iamgenAplanada, int height, int width){
		int n = height;
		int m = width;
		std::vector<vector<int>> nuevaImagen;
		for(int i = 0; i < n ; i ++){
			nuevaImagen.push_back(std::vector<int> ());
			for(int j = 0 ; j < m ; j++){
				//cout << "(" << i <<" , " << j << ")" << endl;
				nuevaImagen[i].push_back(iamgenAplanada[i*m + j]);
			}
		}
		return nuevaImagen;
	}

	void escribirCsv(std::vector<vector<int> >& image){
		fstream sal(savingPath, ios::out);
		int n = image.size();
		int m = image[0].size();


		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				string comaOrEnd = i == m-1 ? "" : ","; 
				sal << image[i][j] << comaOrEnd;
			}
			sal << "\n";
		}
	}


	Image regenerarImagenConDiscretizacion(int ordenDeMagnitud){
		int n = rayos.size();
		Rala A = Rala(n, getWidth()/ordenDeMagnitud* getHeight()/ordenDeMagnitud);
		A.conex = vector< map<int, double> >();
		for(int i = 0 ; i < n ; i ++){
			Rala rayoDiscretizado = Rala(getWidth()/ordenDeMagnitud, getHeight()/ordenDeMagnitud);

			discretizarMatrizDireccionesEnOrdenDe(rayos[i], rayoDiscretizado, ordenDeMagnitud);

			A.conex.push_back(convertirRayoEnFila(rayoDiscretizado));
		}
		cout << "Discretizacion hecha" << endl;
		cout << "Alto de matriz rayos: " << A.n  << endl;
		cout << "Ancho de matriz rayos: " << A.m << endl;

		vector<double> imagenAplanada =  resolverCM(A, tiempos);
		solucion = imagenAplanada;
		cout << "bk6" << endl;
		cout << "IMAGEN APLANADA :" << endl;
		mostrarVector(imagenAplanada);
		vector<vector<int>> imagenDesAplanada = desAplanarImagen(imagenAplanada, getHeight()/ordenDeMagnitud, getWidth()/ordenDeMagnitud);
		Image newImage (imagenDesAplanada, getHeight()/ordenDeMagnitud,  getWidth()/ordenDeMagnitud);
		escribirCsv(imagenDesAplanada);
		cout << "bk7" << endl;
		return newImage;
	}

	//setea en pixel1 y pixel2 dos puntos random dentro de la planilla
	//ACLARACION: siempre pixel1 esta a la izquierda de pixel2
	void createTwoRandomPoints(int n, int m, pair<double,double>& pixel1, pair<double,double>& pixel2){	
		long max_rand = 1000000L;
		double x1 = 0 + (double)m * (rand() % max_rand) / max_rand;
		double x2 = 0 + (double)m * (rand() % max_rand) / max_rand;;

		double y1 = (double)n * (rand() % max_rand) / max_rand;
		double y2 = (double)n * (rand() % max_rand) / max_rand;

		if (x1 > x2) {
			swap(x1,x2);
		}

		pixel1.first = x1;
		pixel1.second = y1;

		pixel2.first = x2;
		pixel2.second = y2;

		//cout << "pixel1: " << x1 << ", " << y1 << endl;
		//cout << "pixel2: " << x2 << ", " << y2 << endl;
	}






	//Agregar ruido con distribucion salt & pepper, paso p probabilidad como argumento y defino t = 1-p,
	//iterando sobre los pixeles obtengo un numero random r y si p<r<t entonces el pixel se mantiene igual,
	//si no, r<p => pixel=negro, r>t => pixel=blanco 
	void addSnPNoiseToSimulation(double p){
		srand (time(NULL));
				
		double thresh = 1 - p;

		//Creo un nuevo vector que despues sera la nueva imagen para pisar
		vector<vector<int> >byteArrayResult(imageMatrix.height, vector<int>(imageMatrix.width));
		
		//Creo vectores planchados para trabajar mejor el algoritmo
		vector<int >byteArray(imageMatrix.height * imageMatrix.width);
		vector<int >source(imageMatrix.height * imageMatrix.width);

		//Primero plancho el imageBuffer asi trabajo mejor
		int sourceIndex = 0;
		for (int i = 0; i < imageMatrix.height; ++i)
		{
			for (int j = 0; j < imageMatrix.width; ++j)
			{
				source[sourceIndex] = imageMatrix.imageBuffer[i][j];
				sourceIndex++;
			}
		}


		for (int i = 0; i < (imageMatrix.height); ++i)
		{
			for (int j = 0; j < (imageMatrix.width); ++j)
			{
				double r = (double) rand() / (RAND_MAX);
				//cout << r << endl;
				if (r<p){
					byteArray[i* imageMatrix.width * 3 + j * 3] = 0;
					byteArray[i* imageMatrix.width * 3 + j * 3 + 1] = 0;
					byteArray[i* imageMatrix.width * 3 + j * 3+ 2] = 0;
				}
				else if (thresh<r){
					byteArray[i* imageMatrix.width * 3 + j * 3] = 255;
					byteArray[i* imageMatrix.width * 3 + j * 3 + 1] = 255;
					byteArray[i* imageMatrix.width * 3 + j * 3 + 2] = 255;
				}
				else{
					byteArray[i* imageMatrix.width * 3 + j * 3] = source[i * imageMatrix.width *3+ j * 3];
					byteArray[i* imageMatrix.width * 3 + j * 3 + 1] = source[i * imageMatrix.width *3+ j * 3 + 1];
					byteArray[i* imageMatrix.width * 3 + j * 3+ 2] = source[i * imageMatrix.width *3+ j * 3+ 2];
					
				}
				
			}
		}

		//Convierto el resultado en vector de vectores
		int byteArrayIndex = 0;
		for (int i = 0; i < imageMatrix.height; ++i)
		{
			for (int j = 0; j < imageMatrix.width; ++j)
			{
				byteArrayResult[i][j] = byteArray[byteArrayIndex];
				byteArrayIndex++;
			}
		}



		imageMatrix.imageBuffer = byteArrayResult;
		//Ancho y alto se conservan
}







	//WRAPUP FUNCTION.

	//PARAMETROS: un vector de rayos, donde cada rayo esta dado por dos puntos. pRuido parametro del ruido a generar. Orden de magnitud para discretizar
	//PRECONDICION:
	//-La instancia de TCSimulator debe estar limpia. Esto es, no puede haber nada en "rayos" ni "tiempos"
	//RETURN: LA INSTANCIA QUEDA SUCIA! (tiene ruido) No reutilizar y crar otra!


	vector<double> obtenerImagenPorRayos(vector<pair<pair<double,double>, pair<double,double> > > coordenadasRayos, double pRuido, int ordenDeMagnitud){

		//Idea:

		//1 - Se agrega ruido a la imagen. Esta instancia NO PUEDE ES REUTILIZABLE. (AL final de la funcion queda sucia)
		//2 - Se generan los rayos a partir de los puntos con la funcion de grego.
		//3 - Por cada rayo, se busca en la imagen el tiempo total en la imagen fuente.
		//4 - Se guarda el rayo (que es una matriz rala) como fila en una nueva matriz A y el tiempo de cada rayo Ti en un vector B
		//5 - Habiendo hecho eso para cada rayo, se discretiza y se resuelve el sistema de ecuaciones.
		//6 - Se devuelve el vector resultado
		

		int cantRayos = coordenadasRayos.size();
		
		
		//1
		 		
		//TIPO DE RUIDO HARDCODEADO. Si se quiere usar otro modificar la linea
		addSnPNoiseToSimulation(pRuido);
		cout << "ya agrego ruido" << endl;

		//2
		generarRayos(cantRayos, coordenadasRayos);

		cout << "Rayos y tiempos creados" << endl;

		//3, 4 y 5
		Image resImagen = regenerarImagenConDiscretizacion(ordenDeMagnitud);

		//"solucion" es otro atributo de TCSimulator para guardar la solucion. 
		//6
		vector<double> resVector = solucion;
		cout << "sistema resuelto. " << endl;

		//Image ya no tiene un metodo para guardar. hay que convertir el csv a png con script de la catedra
		//resImagen->SaveImage(pathSaving, PPM_LOADER_PIXEL_TYPE_RGB_8B);


		cout << "imagen creada. " << endl;


		return resVector;

	}

	vector<double> obtenerVectorImageMatrix(){

		vector<double> res(getWidth()*getHeight(), 0);
		int indiceRes = 0;

		for (int i = 0; i < imageMatrix.height; ++i){
			for (int j = 0; j < imageMatrix.width; ++j)
			{
				res[indiceRes] = (double) imageMatrix.imageBuffer[i][j];
				indiceRes++;
			}
				
		}

		return res; 	
	}

	vector<int> obtenerVectorImageMatrixINT(){

		vector<int> res(getWidth()*getHeight(), 0);
		int indiceRes = 0;

		for (int i = 0; i < imageMatrix.height; ++i){
			for (int j = 0; j < imageMatrix.width; ++j)
			{
				res[indiceRes] = (int) imageMatrix.imageBuffer[i][j];
				indiceRes++;
			}
				
		}

		return res; 	
	}


	

		
private:
	bool isNotInEdge(pair<int,int> pixel){
		return pixel.first != 0 && pixel.first != getWidth()-1 && pixel.second != 0 && pixel.second != getHeight()-1;
	}

	bool areInSameEdge(pair<int,int> pixel1, pair<int,int> pixel2){
		return (pixel1.first == pixel2.first && (pixel1.first == 0 || pixel1.first == getWidth()-1 )) || (pixel1.second == pixel2.second && (pixel1.second = 0 || pixel1.second == getHeight()-1) );
	}
	
};

#endif