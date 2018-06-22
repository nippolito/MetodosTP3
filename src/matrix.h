//#include <vector>

using namespace std;

//multiplica matrices de dimensiones bien definidas y guarda el resultado en C
int multiplicarMatricesDouble(vector<vector<double> >& matrizA, vector<vector<double> >& matrizB, vector<vector<double> >& matrizC ){
	if (matrizA[0].size() != matrizB.size() || matrizC.size() != matrizA.size() || matrizB[0].size() != matrizC[0].size())
		return -1;

	for(int i = 0; i < matrizC.size(); i++){
		for (int j = 0; j < matrizC[i].size(); j++)
		{
			for (int k = 0; k < matrizA[0].size(); ++k)
			{
				matrizC[i][j] += matrizA[i][k] * matrizB[k][j]; 
			} 
		}
	}
	return 1;

}

void multiplicarVectorMatrizDouble(vector<double>& vec, vector<vector<double> >& matriz, vector<double>& vecRes){
	if (vec.size() != matriz.size() || matriz[0].size() != vecRes.size()){
		cout << "Multiplicar vector por matriz con parametros erroneos" << endl;
		return;
	}

	for (int i = 0; i < vecRes.size(); ++i)
	{
		for (int j = 0; j < vec.size(); ++j)
		{
			vecRes[i] += vec[j] * matriz[j][i];
		}
	}

}

//Resta A - B, guardando el resultado en A.
void restarMatrices(vector<vector<double> >& matrizA, vector<vector<double> >& matrizB){
	if (matrizA.size() != matrizB.size() || matrizA[0].size() != matrizB[0].size())
		cout << "Restar Matrices con parametros erroneos" << endl;

	for (int i = 0; i < matrizA.size(); ++i)
	{
		for (int j = 0; j < matrizA[i].size(); ++j)
		{
			matrizA[i][j] = matrizA[i][j] - matrizB[i][j];
		}	
	}
}

void generarMatrizDeVectores(vector<double>& vec1, vector<double>& vec2, vector<vector<double> >& matriz){
	if (matriz.size() != vec1.size() || matriz[0].size() != vec2.size())
		cout << "Generar Matriz de Vectores con parametros erroneos" << endl;

	for (int i = 0; i < vec1.size(); ++i)
	{
		for (int j = 0; j < vec2.size(); ++j)
		{
			matriz[i][j] = vec1[i] * vec2[j];
		}
	}
}

double productoInternoVectores(vector<double>& vec1, vector<double>& vec2){
	if (vec1.size() != vec2.size()){
		cout << "Producto interno de vectores con parametros erroneos" << endl;
		return 0.0;
	}

    double productoInterno = 0.0;
    for(int i=0; i< vec1.size(); i++){
    	productoInterno += (vec1[i] * vec2[i]);
    }
    
    return productoInterno;
}


int multiplicarMatrizVectorDouble(vector<vector<double> >& matriz, vector<double>& vec, vector<double>& vectorRes){
	if (matriz[0].size() != vec.size() || matriz.size() != vectorRes.size())
	{
		cout << "Multiplicar matriz por vector con parametros erroneos"<< endl;
		return -1;	
	}

	for(int i = 0; i < vectorRes.size(); i++){
		for (int j = 0; j < matriz[i].size(); j++)
		{
			vectorRes[i] += matriz[i][j] * vec[j];
		}
	}

	return 1;
}

void multiplicarEscalarPorMatriz(double escalar, vector<vector<double> >& matriz){
	for (int i = 0; i < matriz.size(); ++i)
	{
		for (int j = 0; j < matriz[i].size(); ++j)
		{
			matriz[i][j] = matriz[i][j] * escalar;
		}
	}
}

void trasponerMatriz(vector<vector<double> >& matriz, vector<vector<double> >& matrizT){
	if (matriz.size() != matrizT[0].size() || matriz[0].size() != matrizT.size())
		cout << "Trasponer matriz con parametros erroneos" <<endl;


	for (int i = 0; i < matriz.size(); ++i)
	{
		for (int j = 0; j < matriz[0].size(); ++j)
		{
			matrizT[j][i] = matriz[i][j];
		}
	}

}

void mostrarMatriz(vector<vector<double> >& matriz){
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

void mostrarVector(vector<double>& vec){
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}



void mostrarVectorInt(vector<int>& vec){
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

void mostrarVectorString(vector<string>& vec){
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << ", ";
	}
	cout << endl;	
}

double obtainVectorNorm(vector<double>& vec, unsigned int imageLength){
		double norma2 = 0.0;

		for(int i = 0; i < vec.size(); i++){
			norma2 += vec[i]*vec[i];
		}

		norma2 = sqrt(norma2);

		return norma2;
}

void normalizar(vector<double>& vec){
		double sumaDouble = 0.0;

		for (int i = 0; i < vec.size(); ++i)
		{
			sumaDouble += vec[i]*vec[i];
		}

		sumaDouble = sqrt(sumaDouble);

		for (int i = 0; i < vec.size(); ++i)
		{
			vec[i] = vec[i]/sumaDouble; 
		}
}


void createImageMatrix(){
    	vector<vector<double> > matrix(imageDataSet.size(), vector<double>(m, 0.0));
		for (int i = 0; i < n; ++i)
		{		
        	for( int j = 0; j < m; j++){
      			matrix[i][j] = imageDataSet[i]->obtainPixelValue(j); 
    		}
		}

		basicImagePixelMatrix = matrix;	
}

int maximo (vector<int>& v){
		int res = v[0];
		int n = v.size();
		for(int i = 0 ; i < n; i ++){
			res = res > v[i] ? res : v[i];
		}
 		return res;
}

void obtainImageInVectorDoubles(Image& image, vector<double>& z){
		for(int i = 0 ; i < m ; i ++){
			double pixel = image.obtainPixelValue(i);
			z.push_back(pixel);
		}
} 

void applyBasisChangeToImagePixelsVector(std::vector<double>& imagePixels, vector<double>& imageAfterBasisChange){
		multiplicarMatrizVectorDouble(pcaMatrix,imagePixels,imageAfterBasisChange);
}

vector<double> restaEntreVectores(vector<double> v1, vector<double> v2 ){
		vector<double> res ;
		for(int i = 0 ; i < v1.size(); i ++){
			res.push_back(v1[i] - v2[i]);
		}
		return res;
}

double distanceBetweenVector(vector<double> v1, vector<double> v2 ){
		std::vector<double> v3 = restaEntreVectores(v1,v2);
		sort(v3.begin(), v3.end());
		
		double ac = 0 ;
		for(int i = 0 ; i < v3.size(); i ++){
			ac += v3[i]*v3[i];
		}
		return ac;
}