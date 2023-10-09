/* Name: Prithvi Arunshankar
 * CruzID: parunsha
 * Assignment: pa8
*/
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"
using namespace std;

int main(int argc, char *argv[]) {
    // Check command line for correct number of arguments
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    ifstream iFile;
    ofstream oFile;

    iFile.open(argv[1]);
    if(!iFile.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    oFile.open(argv[2]);
    if(!oFile.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    int line_number = 1;
    string line;
    Dictionary D;

    while(getline(iFile, line)) {
        D.setValue(line.data(), line_number);
        line_number++; 
    }


    if(iFile.is_open()) {
        iFile.close();
    }

    if(oFile.is_open()) {
        oFile << D << endl;
        oFile << D.pre_string();
        oFile.close();
    }
}
