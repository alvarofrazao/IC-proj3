#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <chrono>
namespace fs = std::filesystem;

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    
    if ((int)argc < 3) {
        cerr << "Usage: " << argv[0] << " <input txt file> <model k 3-5>\n";
        return -1;
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    int k = stoi(argv[argc-1]);
    string buffer, temp, line, prob_str, lingua;
    int it = 0;
    vector<string> detect[10], temp_vec;
    bool detect_flag = true;

    string path = "../part2/modelsk";
    path.push_back((char)(k+48));

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
            getline(model,line);
            double sigma = stod(line);
            detect_flag = false;
            while(getline(model,line)) {
                temp.clear();
                for(int i = 0 ; i < k+1 ; i++)
                    temp.push_back(line[i]);
                if(buffer == temp){
                    prob_str = "";
                    for(size_t i = k+1 ; i < size(line) ; i++)
                        prob_str.push_back(line[i]);
                    detect_flag = true;
                    break;
                }
            }
            model.close();
            if(detect_flag)
                detect[it].push_back(lingua);
            else {
                detect[it].push_back("");
            }
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
            if (counter == k*3) {
                cout << lingua << " was detected stating in " << j-k*3 << "º character\n";
                break;
            }
        }
        it++;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;
return 1;
}