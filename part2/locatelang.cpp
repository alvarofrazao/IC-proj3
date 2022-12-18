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
    int k = stoi(argv[argc-1]);
    string buffer, temp, line, prob_str, lingua;
    int it = 0;
    vector<string> detect[10], temp_vec;
    bool detect_flag = true;

    string path = "../part2/models";
    for (const auto & entry : fs::directory_iterator(path)){ 

        lingua = entry.path();
        lingua = lingua.substr (16,size(lingua)-26);

        char c;
        int nbits = 0;
        buffer= "";
        ifstream infile(argv[argc-2]);
        
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
            ifstream model(entry.path());
            detect_flag = false;
            while(getline(model,line)) {
                temp.clear();
                for(int i = 0 ; i < k+1 ; i++)
                    temp.push_back(line[i]);
                if(buffer == temp){
                    prob_str = "";
                    for(size_t i = k+1 ; i < size(line) ; i++)
                        prob_str.push_back(line[i]);
                    nbits = nbits - log2(stod(prob_str));
                    detect_flag = true;
                }
            }
            model.close();
            if(detect_flag)
                detect[it].push_back(lingua);
            else
                detect[it].push_back("");
            for(size_t i  = 0 ; i < size(buffer) ; i++)
                buffer[i] = buffer[i+1];

            infile.get(c);
        }while(!infile.eof());
        infile.close();
        int counter = 0;
        for(size_t j = 1; j < size(detect[it])+1 ; j++){
            if(detect[it][j-1] == lingua)
                counter++;
            else
                counter = 0;
            if (counter == k*2) {
                cout << lingua << " was detected stating in " << j-k*2 << "º character\n";
                break;
            }
        }
        it++;
    }
return 1;
}