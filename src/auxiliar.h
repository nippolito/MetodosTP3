#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"
#include <algorithm> 

	vector<pair<pair<double,double>, pair<double,double> > >  generarMuchasEstrellas(){
		int alturaImagen = 32;
		int max_rand = 10000;
		srand (time(NULL));
		int cantRayosDeCadaUno = 30;
		vector<pair<pair<double,double>, pair<double,double> > > res;
		//diagonales para arriba lado izquierdo
		for(int j = 0 ; j < cantRayosDeCadaUno; j++){
			for(int i = 0 ; i < alturaImagen-1; i ++){
				pair<double,double> pixel1;
				pair<double,double> pixel2;
				double randomEntreCeroYUno = (double)(rand()%max_rand) / (double)(max_rand + 10);

				double x1 = 0;
				double y1 = i +randomEntreCeroYUno;
				
				double x2 = alturaImagen - (i + randomEntreCeroYUno);
				double y2 = alturaImagen-1;

				pixel1.first = x1;
				pixel1.second = y1;

				pixel2.first = x2;
				pixel2.second = y2;

				res.push_back(pair<pair<double,double>, pair<double,double> > (pixel1,pixel2));
			}
		}

		//diagonels para arriba lado abajo

		for(int j = 0 ; j < cantRayosDeCadaUno; j++){
			for(int i = 0 ; i < alturaImagen-1; i ++){
				pair<double,double> pixel1;
				pair<double,double> pixel2;
				double randomEntreCeroYUno = (double)(rand()%max_rand) / (double)(max_rand + 10);

				double x1 = i +randomEntreCeroYUno;
				double y1 = 0;
				
				double y2 = alturaImagen - (i + randomEntreCeroYUno);
				double x2 = alturaImagen-1;

				pixel1.first = x1;
				pixel1.second = y1;

				pixel2.first = x2;
				pixel2.second = y2;

				res.push_back(pair<pair<double,double>, pair<double,double> > (pixel1,pixel2));
			}
		}

		//diagonales para abajo lado izquierda
		for(int j = 0 ; j < cantRayosDeCadaUno; j++){
			for(int i = 1 ; i < alturaImagen; i ++){
				pair<double,double> pixel1;
				pair<double,double> pixel2;
				double randomEntreCeroYUno = (double)(rand()%max_rand) / (double)(max_rand + 10);

				double x1 = 0;
				double y1 = i +randomEntreCeroYUno;
				
				double x2 = i + randomEntreCeroYUno;
				double y2 = 0;

				pixel1.first = x1;
				pixel1.second = y1;

				pixel2.first = x2;
				pixel2.second = y2;

				res.push_back(pair<pair<double,double>, pair<double,double> > (pixel1,pixel2));
			}
		}

		//diagonales para abajo lado arriba
		for(int j = 0 ; j < cantRayosDeCadaUno; j++){
			for(int i = 1 ; i < alturaImagen; i ++){
				pair<double,double> pixel1;
				pair<double,double> pixel2;
				double randomEntreCeroYUno = (double)(rand()%max_rand) / (double)(max_rand + 10);

				double x1 = i +randomEntreCeroYUno;
				double y1 = alturaImagen-1;
				
				double x2 = alturaImagen-1;
				double y2 = alturaImagen - (i + randomEntreCeroYUno);

				pixel1.first = x1;
				pixel1.second = y1;

				pixel2.first = x2;
				pixel2.second = y2;

				res.push_back(pair<pair<double,double>, pair<double,double> > (pixel1,pixel2));
			}
		}


		return res;
	}


	void mostrarPixel(pair<double,double> p){
		cout << "(" << p.first << "," << p.second <<")";
	}


	vector<vector<int> > desAplanarImagen(std::vector<double>& iamgenAplanada, int height, int width){
		int n = height;
		int m = width;
		std::vector<vector<int>> nuevaImagen;
		for(int i = 0; i < n ; i ++){
			nuevaImagen.push_back(std::vector<int> ());
			for(int j = 0 ; j < m ; j++){
				//cout << "(" << i <<" , " << j << ")" << endl;
				nuevaImagen[i].push_back(iamgenAplanada[i*m + j] + 0.4999);
			}
		}
		return nuevaImagen;
	}

	int pasarDe16a8(int num){
		return num * 255 / 65235;
	}

	int pasarDe8a16(int num){
		return num * 65235 / 255;
	}

	int parsearEnRango16(int num){
		return num < 0 ? 0 : num > 65235 ? 65235 : num;
	}

	int parsearEnRango8(int num){
		return num < 0 ? 0 : num > 255 ? 255 : num;
	}

	void escribirCsv(std::vector<vector<int> >& image, string path){
		// cout << "el saving path es" << endl;
		fstream sal(path, ios::out);
		int n = image.size();
		int m = image[0].size();


		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				string comaOrEnd = j == m-1 ? "" : ","; 
				int numeroAImprimir = image[i][j];
				sal << numeroAImprimir << comaOrEnd;
			}
			sal << "\n";
		}
	}




	double ECM(vector<double> v1, vector<double> v2){
		double res = 0;
		for(int i = 0; i < v1.size(); i++){
			res += pow((v1[i] - v2[i]), 2);
		}
		res = res / v1.size();
		return res;
	}

	vector<int> pasarVectorDe16a8(vector<int>& vec){
		vector<int> res;
		for(int i = 0; i < vec.size(); i++){
			res.push_back(pasarDe16a8(vec[i]));
		}
		return res;
	} 

	vector<int> pasarVectorDe8a16(vector<int>& vec){
		vector<int> res;
		for(int i = 0; i < vec.size(); i++){
			res.push_back(pasarDe8a16(vec[i]));
		}
		return res;
	} 

	vector<double> normalizar16Bit(vector<double>& vec){
		vector<double> res;
		for(int i = 0; i < vec.size(); i++){
			res.push_back((double) vec[i] / 65235);
		}
		return res;	
	}

	vector<double> normalizar8Bit(vector<double>& vec){
		vector<double> res;
		for(int i = 0; i < vec.size(); i++){
			res.push_back((double) vec[i] / 255);
		}
		return res;	
	}

	vector<double> normalizar (vector<double>& vec){
		double blanco = 0; 
		int n = vec.size();
		for(int i = 0 ; i < n ; i ++){
			blanco = vec[i] > blanco ? vec[i] : blanco;
		}

		vector<double> res;
		for(int i = 0; i < vec.size(); i++){
			res.push_back((double) vec[i] / blanco);
		}
		return res;	
	}


	void mostrarRayos(){
		vector<pair<pair<double,double>, pair<double,double> > > muchasEstrellas = generarMuchasEstrellas();
		int n = muchasEstrellas.size();
		for(int i =0 ; i<  n; i ++){
			cout <<"pixel1: ";mostrarPixel(muchasEstrellas[i].first); cout <<" - pixel2: "; mostrarPixel(muchasEstrellas[i].second); cout <<"\n";
		}
	}

	vector<double> pasarDeImagenAVecDouble(vector<vector<int> > pixeles){
		vector<double> res ;
		for(int i = 0 ; i < pixeles.size(); i ++){
			for(int j = 0 ; j < pixeles[0].size(); j++){
				res.push_back((double)pixeles[i][j]);
			}
		}
		return res;
	}

	int llenarRenglon(vector<int>& pixeles, string renglon){
		int n = renglon.length();
		int lastComa = 0 ;
		for(int i = 0 ; i < n ; i ++){
			if(renglon[i] == ','){
				int vel = stoi(renglon.substr(lastComa,i-lastComa));
				pixeles.push_back(vel);
			 	lastComa = i+1;
			}
		}
		pixeles.push_back(stoi(renglon.substr(lastComa,n-lastComa)));
		return pixeles.size();
	}



	vector<vector<int> > levantarCsv(string path){
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

	    return pixeles;
	}


