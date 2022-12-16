#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm> // std::find
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
    // int a = 1;
    map<string, map<char, int>> probs = {};
    string temp;
    vector<string> symbols;
    vector<char> alphabet = {};
    map<string, map<char, int>>::iterator outer;
    map<char, int> tempmap;
    map<char, int>::iterator inner;
    char p = 'o';
    string file_name = argv[argc - 1];
    fstream files;
    files.open(file_name, ios::in);
    string m;
    char r;
    while (getline(files, m))
    {
        for (int s = 0; m[s + k] != '\0'; s++) // ultimos k characteres da string sao ignorados (ou os k-1? nao fiz as contas)
        {
            temp.clear();
            tempmap.clear();
            for (int i = 0; i < k; i++)
            {
                r = m[s + i];
                temp.push_back(r);
                if (find(alphabet.begin(), alphabet.end(), m[s + i]) == alphabet.end())
                {
                    alphabet.push_back(r);
                }
            }
            p = m[s + k];
            outer = probs.find(temp);
            if (outer == probs.end())
            {
                tempmap.insert(pair<char, int>(p, 1));
                probs.insert(pair<string, map<char, int>>(temp, tempmap));
                // se ele nao encontrar a string de k chars no mapa externo, ele cria logo uma entrada tanto no mapa interno como no externo
                // ignorando assim o passo de procura pelo char
            }
            else
            {
                inner = outer->second.find(p);
                if (inner != outer->second.end())
                {
                    inner->second++;
                }
                else
                {
                    outer->second.insert(pair<char, int>(p, 1));
                }
            }
        }
    }
    files.close();
    int sigma = (int)alphabet.size();

    files.open(file_name.insert(file_name.length() - 4, "-class"), ios::out);
    for (auto t : probs)
    {
        for (auto y : t.second)
        {
            files << t.first << y.first << y.second << '\n';
        }
    }
    files.close();

    double nbits = 0;
    int n;
    double num;
    double den;
    double pp;
    files.open(file_name, ios::in);
    while (getline(files, m))
    {
        for (int s = 0; m[s + k] != '\0'; s++)
        {
            temp.clear();
            for (int i = 0; i < k; i++)
            {
                temp.push_back(m[s + i]);
            }
            p = m[s + k];
            outer = probs.find(temp);
            n = (int)outer->second.size();

            if (outer != probs.end())
            {
                inner = outer->second.find(p);
                if (inner != outer->second.end())
                {
                    num = alfa + inner->second;
                    den = n + (alfa * sigma);
                    pp = num / den;
                    nbits = nbits - log2(pp); // nao sei se estes calculos tao bem
                }
            }
        }
    }
    files.close();
    cout << "string entropy = " << nbits << '\n';
    cout << sigma << '\n';
    return 0;
}
