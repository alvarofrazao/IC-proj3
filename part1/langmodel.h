#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm> 
#include <stdlib.h>

class langmodel
{
    private:
        int k;
        int alfa;
        std::map<std::string,std::map<char,int>> probs = {};
        std::map<char,int> tempmap;
        std::string buffer;
    public:
        langmodel(int k_in, int alfa_in,const char *file) {
            k = k_in;
            alfa = alfa_in;
            std::ifstream fw(file, std::ifstream::in);
            while(!fw.eof())
            {
                tempmap.clear();
                getline(fw,buffer);
                if(buffer != "")
                {
                    char point = buffer[k];
                    int count = stoi(buffer.substr(k+1, buffer.size()-k+1));
                    tempmap.insert(std::pair<char,int>(point,count));
                    probs.insert(std::pair<std::string,std::map<char,int>>(buffer.substr(0,k),tempmap));
                }
            }
        }
};