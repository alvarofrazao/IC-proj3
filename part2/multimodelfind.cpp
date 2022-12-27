#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "lang_model.h"
using namespace std;
namespace fs = std::filesystem;

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    if ((int)argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <input txt file> <number of models used>\n";
        return -1;
    }

    fstream files;
    files.open(argv[argc - 2], ios::in);
    vector<lang_model> models;
    string path = "../part2/multikmodels";
    vector<char> init = {'a', 'e', 'i', 'o', 'u'};

    double alfa = 1;
    int counter = 0;
    int mdl_n= stoi(argv[argc-1]);

    for (const auto &entry : fs::directory_iterator(path))
    {
        if(counter < mdl_n)
        {
            break;
        }
        models.push_back(lang_model(entry.path(), alfa));
        counter++;
    }

    if(models.size()>(size_t)mdl_n)
    {
        cerr << "Model list inconsistent with <number of models used>\n";
        return -1;
    }

    string buffer;
    int model_idx = rand() % (int)models.size(); //first model; "randomly" chosen


    int j = 0;
    int cur_k = models[model_idx].get_k();
    char storage = ' ';
    double prob;
    double total = 0;

    for (int i = 0; i <= cur_k; i++)
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

    int low_size = models[model_idx].get_size();
    pair<int,int> presence;

    while(!files.eof())
    {
        while((int)buffer.size() > cur_k-1)
        {
            buffer.erase(buffer.begin());
        }

        while((int)buffer.size() < cur_k-1)
        {
            files.read(&storage, sizeof(char));
            buffer.push_back(storage);
        }

        files.read(&storage, sizeof(char));
        buffer.push_back(storage);

        prob += models[model_idx].model_find(buffer);

        for(int j = 0; j < (int)models.size();j++)
        {
            presence = models[j].check_presence(buffer);
            if(j != model_idx)
            {
                if(presence.first)
                {
                    if((presence.second < low_size) || (models[model_idx].get_mstr() > models[j].get_mstr()))
                    {
                        low_size = presence.second;
                        model_idx = j;
                        cur_k = models[j].get_k();
                    }
                }
            }
        }
        buffer.erase(buffer.begin());
    }


    return 0;
}
    