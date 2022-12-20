#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

int main(int argc, char *argv[]) {
    
    if ((int)argc < 3) {
        cerr << "Usage: " << argv[0] << " <input txt file> <model k>\n";
        return -1;
    }
    double a = 1;
    int k = stoi(argv[argc-1]);
    string buffer, temp, line, prob_str, lingua;
    double best = MAXFLOAT;

    string path = "../part2/models";
    for (const auto & entry : fs::directory_iterator(path)){ 

        char c;
        double nbits = 0;
        buffer= "";
        bool flag;
        ifstream infile(argv[argc-2]);
        
        for(int i = 0 ; i < k+1 ; i++) {
            infile.get(c);
            if( c != '\n')
                buffer.push_back(c);
            else
                buffer.push_back('|');
        }
        int corretas = 0, incorretas = 0;
        do{
            if( c != '\n')
                buffer[k] = c; 
            else
                buffer[k] = '|';
            ifstream model(entry.path());
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
                    corretas++;
                } 
            }
            if(!flag) 
                nbits = nbits - log2(a/(a*sigma));

            model.close();

            for(size_t i  = 0 ; i < size(buffer) ; i++)
                buffer[i] = buffer[i+1];

            infile.get(c);

        }while(!infile.eof());
        if ( nbits < best){
            best = nbits;
            lingua= entry.path();
        }
        infile.close();
    }
    cout << "The text is in "<< lingua.substr (16,size(lingua)-26)<< ".\n";
return 1;
}