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
    if ((int)argc < 4)
    {
        cerr << "Usage: " << argv[0] << " <input txt file> <k> <a>\n";
        return 1;
    }

    int k = stoi(argv[argc - 2]);
    double alfa = stod(argv[argc - 1]);
    vector<char> init = {'c', 'o', 'n', 't', 'a'};
    vector<char> alphabet = {};

    map<char, double>::iterator inner;
    map<string, map<char, double>>::iterator outer;
    map<char, double> tempmap;
    map<string, map<char, double>> prob = {};

    string buffer;
    int j = 0;
    for (int i = 0; i < k; i++)
    {
        if (j < 5)
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

    string file_name = argv[argc - 3];
    fstream files;
    files.open(file_name, ios::in);
    char storage;
    string map_insert;
    while (files.read(&storage, sizeof(char)))
    {
        if (storage == '\n')
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

        for (int j = 0; j < k; j++)
        {
            map_insert.push_back(buffer[j]);
        }
        if ((int)map_insert.size() >= k)
        {
            outer = prob.find(map_insert);
            if (outer == prob.end())
            {
                tempmap.insert(pair<char, double>(storage, 1));
                prob.insert(pair<string, map<char, double>>(map_insert, tempmap));
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
                    outer->second.insert(pair<char, double>(storage, 1));
                }
            }
            // rotate(buffer.begin(),buffer.begin()+1,buffer.end());
        }
        buffer.erase(buffer.begin());
    }
    files.close();
    double sigma = prob.size(); // trocar alphabet
    double n;
    double num;
    double den;
    double pp;
    files.open(file_name.insert(file_name.length() - 4, "-model"), ios::out);
    files << sigma << "\n";
    for (auto t : prob)
    {
        n = t.second.size();
        for (auto y : t.second)
        {
            num = alfa + y.second;
            den = n + (alfa * sigma);
            pp = num / den;
            files << t.first << y.first << pp << '\n';
        }
    }
    files.close();
    return 0;
}
