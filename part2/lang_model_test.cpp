#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "lang_model.h"
#include <cstdlib>
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    if ((int)argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <input txt file> <model k> <model alfa>\n";
        return -1;
    }
    // int k = stoi(argv[argc - 2]);
    // double alfa = stod(argv[argc - 1]);
    int k = 4;
    int alfa = 1;
    vector<char> init = {'a', 'e', 'i', 'o', 'u'};

    fstream files;
    files.open(argv[argc - 3], ios::in);
    vector<lang_model> models;

    /*lang_model danish("../part2/models/danish-model.txt",k,alfa);
    lang_model english("../part2/models/english-model.txt",k,alfa);
    lang_model german("../part2/models/german-model.txt",k,alfa);
    lang_model french("../part2/models/french-model.txt",k,alfa);
    lang_model portuguese("../part2/models/portuguese-model.txt",k,alfa);
    lang_model spanish("../part2/models/spanish-model.txt",k,alfa);*/

    string path = "../part2/models";
    for (const auto &entry : fs::directory_iterator(path))
    {
        models.push_back(lang_model(entry.path(), k, alfa));
    }

    bool new_seg = true;
    char storage = ' ';
    vector<int> seg_ipos = {};
    vector<int> seg_fpos = {};
    vector<int> miss_count = {};
    vector<int> change_count = {};


    pair<int,double> function_find;
    int cseg_pos;
    string buffer;

    int j = 0;
    for (int i = 0; i <= k; i++)
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

    double prob;
    double cur_low = MAXFLOAT;
    string cur_lang;
    string old_lang;
    vector<double> avg = {};

    vector<string> lang_det = {};

    for (size_t j = 0; j < models.size(); j++)
    {
        for (size_t j = 0; j < models.size(); j++)
        { 
            prob = models[j].model_find(buffer);
            if(prob < cur_low)
            {
                old_lang = models[j].get_lang();
                cur_low = prob;
            }
        }
        avg.push_back(0);
        miss_count.push_back(0);
    }
    buffer.erase(buffer.begin());
    cout << "Language detected in vowel buffer: "<< old_lang << '\n';


    //bool first = true;
    int window_len = 20;
    double temp;
    cur_low = MAXFLOAT;
    int run_count = 0;

    while (!files.eof())
    {
        run_count++;
        if (new_seg)
        {
            cseg_pos = files.tellg();
            new_seg = false;
        }
        for (int i = 0; i < window_len; i++)
        {
            
            files.read(&storage, sizeof(char));
            buffer.push_back(storage);
            if (files.eof())
            {
                break;
            }

            for (size_t j = 0; j < models.size(); j++)
            {

                prob = models[j].model_find(buffer);
                if (prob == models[j].get_mstr())
                {
                    miss_count[j]++;
                }
                avg[j] -= log2(prob);
            }
            buffer.erase(buffer.begin());
        }
        for (size_t j = 0; j < models.size(); j++)
        {
            temp = miss_count[j] / window_len;
            avg[j] = avg[j]* (1-temp);
            if(avg[j] < cur_low)
            {
                cur_lang = models[j].get_lang();
                cur_low = avg[j];
            }
        }
        //cur_low = cur_low*1.2;
        if(cur_lang != old_lang)
        {
            lang_det.push_back(old_lang);
            old_lang = cur_lang;
            seg_ipos.push_back(cseg_pos);
            seg_fpos.push_back(files.tellg());
            new_seg = true;

            cur_low *= 1.2;
        }
    }

    for (size_t i = 0; i < lang_det.size(); i++)
    {
        cout << lang_det[i] << " segment detected, starting in position " << seg_ipos[i];
        cout << " ending in position: " << seg_fpos[i] << '\n';
    }
    cout << "Ran " << run_count << " times\n";
    return 0;
}