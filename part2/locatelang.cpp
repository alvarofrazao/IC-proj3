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
    string buffer, temp, line, prob_str, language;
    int it = 0;
    vector<double> detect[10], detect_means[10];
    vector<string> languages_list, detect_final,temp_vec;
    bool detect_flag = true;
    double mean;

    string path = "../part2/models";
    for (const auto & entry : fs::directory_iterator(path)){ 

        language = entry.path();
        language = language.substr (16,size(language)-26);
        languages_list.push_back(language);

        char c;
        double a = 1;
        double nbits = 0;
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
                    nbits =  - log2(stod(prob_str));
                    detect_flag = true;
                }
            }
            model.close();
            if(!detect_flag)
                nbits = - log2(a/(a*sigma));

            detect[it].push_back(nbits);
            for(size_t i  = 0 ; i < size(buffer) ; i++)
                buffer[i] = buffer[i+1];

            infile.get(c);
        }while(!infile.eof());

        for( size_t i = 0 ; i < size(detect[it])-k ; i++) {
            mean = 0;
            for(int n = 0; n < k; n++)
                mean = mean + detect[it][i+n];
            detect_means[it].push_back(mean/k);
        }
    
        infile.close();
        it++;
    };
    double best;
    int best_j;
    for( int i = 0 ; i < size(detect_means[0]) ; i++){
        best = MAXFLOAT;
        for(int  j = 0; j< size(languages_list) ; j++){
            if(detect_means[j][i]< best){
                best_j = j;
                best = detect_means[j][i];
            }
        }
        detect_final.push_back(languages_list[best_j]);
    }
    int o = 0;
    int limit;
    string last_language = "";
    
    for(int i = 0; i<size(detect_final) ; i++) {
        temp_vec.push_back(detect_final[i]);
        o++;

        if( (o%10) == 0) {
            limit = 0;
            for(auto y: languages_list) {
                if(count(temp_vec.begin(), temp_vec.end(), y) > limit) {
                    limit = count(temp_vec.begin(), temp_vec.end(), y);
                    language = y;
                }
                else if(count(temp_vec.begin(), temp_vec.end(), y) == limit){
                    language = "Multiple languages ";
                    break;
                }
            }
            if(last_language != language) {
                cout << language<< " detected in the "<< i-9<< "º"<<"\n";
                last_language = language;
            }
            temp_vec.clear();
        }
    }

return 1;
}