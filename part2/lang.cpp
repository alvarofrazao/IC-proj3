#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    
    if ((int)argc < 3) {
        cerr << "Usage: " << argv[0] << " <input txt file> <model txt file>\n";
        return -1;
    }

    int k = 5;
    string buffer, temp, line, prob_str;
    ifstream infile(argv[argc-2]);
    ifstream model;

    char c;
    int nbits = 0;
    double prob;

    for(int i = 0 ; i < k+1 ; i++) {
        infile.get(c);
        if( c != '\n')
            buffer.push_back(c);
        else
            buffer.push_back('|');
    }
    do{
        if( c != '\n')
            buffer[k] = c; 
        else
            buffer[k] = '|';
        model.open(argv[argc-1]);
        while(getline(model,line)) {
            temp.clear();
            for(int i = 0 ; i < k+1 ; i++)
                temp.push_back(line[i]);
            if(buffer == temp){
                prob_str = "";
                for(size_t i = k+1 ; i < size(line) ; i++)
                    prob_str.push_back(line[i]);
                nbits = nbits - log2(stod(prob_str));
            }
        }
        model.close();

        for(size_t i  = 0 ; i < size(buffer) ; i++)
            buffer[i] = buffer[i+1];

        infile.get(c);
    }while(!infile.eof());
    cout << "File entropy = " << nbits << '\n';
    infile.close();
return 1;
}