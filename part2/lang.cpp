#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    
    if ((int)argc < 3) {
        cerr << "Usage: " << argv[0] << " <input txt file> <model txt file> <model k>\n";
        return -1;
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    int k = stoi(argv[argc-1]);
    int a = 1;
    string buffer, temp, line, prob_str;
    ifstream infile(argv[argc-3]);
    ifstream model;

    char c;
    int nbits = 0;
    bool flag;


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
        model.open(argv[argc-2]);
        getline(model,line);
        double sigma = stod(line);
        flag = false;
        while(getline(model,line)) {
            temp.clear();
            for(int i = 0 ; i < k+1 ; i++)
                temp.push_back(line[i]);
            if(buffer == temp){
                prob_str = "";
                for(size_t i = k+1 ; i < size(line) ; i++)
                    prob_str.push_back(line[i]);
                nbits = nbits - log2(stod(prob_str));
                flag = true;
                break;
            }
        }
        model.close();
        if(!flag) 
            nbits = nbits - log2(a/(a*sigma));

        for(size_t i  = 0 ; i < size(buffer) ; i++)
            buffer[i] = buffer[i+1];

        infile.get(c);
    }while(!infile.eof());
    cout << "File entropy = " << nbits << '\n';
    infile.close();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;
return 1;
}