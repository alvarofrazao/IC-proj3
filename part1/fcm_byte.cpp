#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm> // std::find
#include <cstddef>
using namespace std;

int main(int argc, char *argv[])
{
    if ((int)argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input txt file>\n";
        return 1;
    }

    int k = 5;
    int alfa = 1;
    vector<char> init = {'a','e','i','o','u'};
    vector<char> alphabet = {};


    map<char,int>::iterator inner;
    map<string,map<char,int>>::iterator outer;
    map<char,int> tempmap;
    map<string,map<char,int>> prob = {};

    string buffer;
    int j = 0;
    for (int i = 0; i < k; i++)
    {
        if(j < 5)
        {
            buffer.push_back(init[j]);
        }
        else
        {
            j = 0;
            buffer.push_back(init[j]);
        }
        j++;
    }


    string file_name = argv[argc - 1];
    fstream files;
    files.open(file_name, ios::in);
    char storage;
    string map_insert;
    cout << "read start\n";
    while(files.read(&storage,sizeof(char)))
    {
        if(storage == '\n')
        {
            storage = '|';
        }
        tempmap.clear();
        map_insert.clear();
        buffer.push_back(storage);

        if (find(alphabet.begin(), alphabet.end(), storage) == alphabet.end())
        {
            alphabet.push_back(storage);
        }
        
        for(int j = 0; j < k; j++)
        {
            map_insert.push_back(buffer[j]);
        }
        
        outer = prob.find(map_insert);
        if (outer == prob.end())
        {
            tempmap.insert(pair<char, int>(storage, 1));
            prob.insert(pair<string, map<char, int>>(map_insert, tempmap));
        }
        else
        {
            inner = outer->second.find(storage);
            if (inner != outer->second.end())
            {
                inner->second++;
            }
            else
            {
                outer->second.insert(pair<char, int>(storage, 1));
            }
        } 
        //rotate(buffer.begin(),buffer.begin()+1,buffer.end());
        buffer.erase(buffer.begin());
    }
    files.close();
    cout << "read over\n";
    cout << "prob calc start\n";
    int sigma = alphabet.size();
    int n;
    double num;
    double den;
    double pp;
    files.open(file_name.insert(file_name.length() - 4, "-class"), ios::out);
    cout << "filestream open\n";
    for (auto t : prob)
    {
        n = t.second.size();
        for (auto y : t.second)
        {
            num = alfa + y.second;
            den = n + (alfa + sigma);
            pp = num/den;
            files << t.first << y.second << pp << '\n';
        }
    }
    files.close();
    cout << "filestream closed\n";
    return 0;
}
