#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>    // std::find
using namespace std;


int main(/*int argc, char *argv[]*/) {
    
    int k = 5;
    //int a = 1;
    map<string,map<char,int>> probs = {};
    string temp;
    vector<string> symbols;
    map<string,map<char,int>>::iterator outer;
    map<char,int> tempmap;
    map<char,int>::iterator inner;
    char p = 'o';
    int element_count;

    string m = "Among all the useful compression algorithms of today, finite context modeling is the base model that we generally use.  Both the very fast compressors as well as the state-of-the-art compressors will use it.  The best known methods are the ppm (Prediction by Partial Matching) variants, which are all fundamentally alike except for their escape code models.  But even simpler models like huffman coding are really finite context models, albeit single-character contexts.  Even archaic methods like the innumerable lz variants are using finite context models to select offsets.  Basically, the entropy of a data set is as low as we can ever hope to compress any given dataset.  Arithmetic coders achieve bitrates almost exactly equal to the actual entropy.  However, we can augment these coders with pre-processes and predictors to transform the data to a specific subspace in which the entropy is lower.  e.g. A context like is actually uncompressible because every character is absolutely unique.  However, in a differential space, we can write it as  which is very low entropy because it has only 2 characters.  The differential space transformation can be thought of as a 1st-order context because it is a comparison against the immediately prior character.  In reality, that's an oversimplification of what context models represent, as there is no real probability distribution in a differential transformation";
    
    for(int s = 0; m[s+k] != '\0'; s++) //ultimos k characteres da string sao ignorados (ou os k-1? nao fiz as contas)
    {
        temp.clear();
        tempmap.clear();
        cout << "1\n";
        for(int i = 0; i < k;i++)
        {
            temp.push_back(m[s+i]);
            cout << "temp insert\n";
        }
        cout << p << "\n";
        p = m[s+k];
        cout << p << "\n";
        outer = probs.find(temp);
        if(outer == probs.end())
        {
            cout <<"nofind\n";
            tempmap.insert(pair<char,int>(p,1));
            probs.insert(pair<string,map<char,int>>(temp,tempmap));
            //se ele nao encontrar a string de k chars no mapa externo, ele cria logo uma entrada tanto no mapa interno como no externo
            //ignorando assim o passo de procura pelo char
        }
        else
        {
            cout <<"find\n";
            inner = outer->second.find(p);
            if(inner != outer->second.end())
            {
                cout << "increments\n";
                inner->second++;
            }
            else
            {
                cout << "inserts\n";
                outer->second.insert(pair<char,int>(p,1));
            }
        }
        element_count = s;
    }

    for(auto t: probs)
    {
        for (auto y: t.second)
        {
            y.second = y.second/element_count;
        }
    }

    for(auto t: probs)
    {
        for (auto y: t.second)
        {
            cout << t.first << " " << y.first << " " << y.second << '\n';
        }
    }

    double entropy = 0;
    for(int s = 0; m[s+k] != '\0'; s++)
    {
        temp.clear();
        for(int i = 0; i < k;i++)
        {
            temp.push_back(m[s+i]);
        }
        p = m[s+k];
        outer = probs.find(temp);
        if(outer != probs.end())
        {
            inner = outer->second.find(p);
            if(inner != outer->second.end())
            {
                entropy = entropy + (log2(inner->second)*inner->second); //nao sei se estes calculos tao bem
            }
        }
    }
    cout << "string entropy = " << entropy << '\n';
    return 0;
}
