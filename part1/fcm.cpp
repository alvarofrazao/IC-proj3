#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>    // std::find
using namespace std;


int main(int argc, char *argv[]) {
    
    int k = 5;
    int a = 1;
    map<string,map<char,int>> probs;
    string temp;
    vector<string> symbols;

    string m = "Among all the useful compression algorithms of today, finite context modeling is the base model that we generally use.  Both the very fast compressors as well as the state-of-the-art compressors will use it.  The best known methods are the ppm (Prediction by Partial Matching) variants, which are all fundamentally alike except for their escape code models.  But even simpler models like huffman coding are really finite context models, albeit single-character contexts.  Even archaic methods like the innumerable lz variants are using finite context models to select offsets.  Basically, the entropy of a data set is as low as we can ever hope to compress any given dataset.  Arithmetic coders achieve bitrates almost exactly equal to the actual entropy.  However, we can augment these coders with pre-processes and predictors to transform the data to a specific subspace in which the entropy is lower.  e.g. A context like is actually uncompressible because every character is absolutely unique.  However, in a differential space, we can write it as  which is very low entropy because it has only 2 characters.  The differential space transformation can be thought of as a 1st-order context because it is a comparison against the immediately prior character.  In reality, that's an oversimplification of what context models represent, as there is no real probability distribution in a differential transformation";
    for(size_t i = 4 ; i < m.size() ; i++) {
        temp = "";
        for( size_t j = i-4 ; j<= i ; j++)
            temp.push_back(m[j]);
        if(find(symbols.begin(),symbols.end(),temp)==symbols.end())
            symbols.push_back(temp);

    }
    for(auto x: symbols)
        cout << x << "\n";
    // FAZER FOR PARA CONTAR E GUARDAR OS CARACTERES DEPOIS DE CADA SYMBOL
    
    //std::pair<int, std::vector<int>>(i,temp2)
    return 0;
}
