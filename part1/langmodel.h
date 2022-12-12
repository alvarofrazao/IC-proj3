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
        std::string temp;
        std::vector<std::string> symbols;
        std::vector<char> alphabet = {};
        std::map<std::string,std::map<char,int>>::iterator outer;
        std::map<char,int> tempmap;
        std::map<char,int>::iterator inner;
    public:
        langmodel(int k_in, int alfa_in,const char *file)
        {
            std::string buffer;
            k = k_in;
            alfa = alfa_in;
            std::ifstream fw(file, std::ifstream::in);
            while(!fw.eof())
            {
                tempmap.clear();
                getline(fw,buffer);
                if(buffer != "")
                {
                    char point = buffer[k_in];
                    std::string con_s = buffer.substr(k+1, buffer.size()-k+1);
                    int count = stoi(con_s);
                    std::cout << con_s << "\n"; 
                    //tempmap.insert(std::pair<char,int>(point,count));
                }
            }
        }
};