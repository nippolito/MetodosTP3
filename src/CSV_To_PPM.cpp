#include "Image.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


int main(int argc, char *argv[]){
	filebuf fb;
	fb.open (argv[1],std::ios::in);
	std::istream fs (&fb);

    string s;
    int i = 0; 
    while(getline(fs,s,',')){
    	//int std::stoi (str_dec,&sz)
        cout << s << "-" << i << " / ";
        i++;
    }

    return 0 ;
}
