#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class TCSimulator
{
public:
	int createTCRay(pair<int,int> pixel1, pair<int,int> pixel2, vector<vector<int>>& distances){
		//nos aseguramos que el primer pixel tenga un x menor a pixel2
		//los rayos pueden "ir en sentido contrario" pero para la simulacion los trataremos SIEMPRE
		//de izquierda a derecha
		//PRECONDICION OBLIGATORIA: ambos puntos deben estar en los bordes, osea x = 0 o x = ancho o y = 0 o y = alto
		if ( isNotInEdge(pixel1) || isNotInEdge(pixel2) || areInSameEdge(pixel1,pixel2)){
			cout << "Pixeles no estan en bordes distintos" << endl;
			return 0;
		}

		if (pixel2.first < pixel1.first)
		{
			pair<int,int> tempPair = pixel1;
			pixel1 = pixel2;
			pixel2 = tempPair;
		}

		double a = (double) (pixel2.second - pixel1.second) / (pixel2.first - pixel1.first);
		double b = pixel1.second - a * pixel1.first;

		cout << "y = " << a << "x + (" << b <<")" << endl;

		for (int i = pixel1.first; i < pixel2.first-1; ++i)
		{
			for (int j = (int) floor(a*i + b); j =< a*(i+1) + b; ++j)
			{
				cout << i << " " << j << endl;
				distances[i][j] = 1;
			}
		}


		
	}

	TCSimulator(string imageSimulatedPath){
		imageMatrix = new Image(imageSimulatedPath);
	}

	~TCSimulator(){
		delete imageMatrix;		
	}

	int getWidth(){
		return imageMatrix->width;
	}


	int getHeight(){
		return imageMatrix->height;
	}
		
private:
	bool isNotInEdge(pair<int,int> pixel){
		return pixel.first != 0 && pixel.first != getWidth()-1 && pixel.second != 0 && pixel.second != getHeight()-1;
	}

	bool areInSameEdge(pair<int,int> pixel1, pair<int,int> pixel2){
		return (pixel1.first == pixel2.first && (pixel1.first == 0 || pixel1.first == getWidth()-1 )) || (pixel1.second == pixel2.second && (pixel1.second = 0 || pixel1.second == getHeight()-1) );
	}

	
	Image* imageMatrix;

};