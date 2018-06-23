#include "Image.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string>

using namespace std;


void llenarRenglon(vector<int>& pixeles, string renglon){
	int n = renglon.length();
	int lastComa = 0 ;
	for(int i = 0 ; i < n ; i ++){
		if(renglon[i] == ','){
			pixeles.push_back(stoi(renglon.substr(lastComa,i-lastComa)));
		 	lastComa = i+1;
		}
	}
	pixeles.push_back(stoi(renglon.substr(lastComa,n-lastComa)));
}

int main(int argc, char *argv[]){
	filebuf fb;
	fb.open (argv[1],std::ios::in);
	std::istream fs (&fb);

    string s;

    vector<string> renglones; 
    int cantDeRenglones = 0 ;
    while(getline(fs,s)){
    	//int number = std::stoi (s,nullptr,10);
        cout << s << endl;
        renglones.push_back(s);
        cantDeRenglones ++ ;
    }

    vector<vector<int> > pixeles;
    for(int i = 0 ;i < cantDeRenglones; i++){
    	pixeles.push_back(std::vector<int> ());
    }
    for(int i = 0 ;i < cantDeRenglones; i ++){
    	llenarRenglon(pixeles[i], renglones[i]);
    }


    return 0 ;
}
