#include "Image.cpp"
#include "TCSimulator.cpp"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>
#include <string>
#include <chrono>
#include "matrizRala.h"


using namespace std;

int main(){
	string path = "../imgs_TC/tomo.ppm";
	TCSimulator Simulator(path);
	vector<vector<int>> matrizDistancias(Simulator.getHeight(), vector<int>(Simulator.getWidth()));
	int rayTime = Simulator.createTCRay(pair<int,int>(0,5), pair<int,int>(99,5), matrizDistancias);
	return 1;
}