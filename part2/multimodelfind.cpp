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
    string path = "../part2/multimodel";
    vector<char> init = {'a', 'e', 'i', 'o', 'u'};

    vector<double> alfa = {0.05, 0.75, 0.005};
    vector<int> k = {4, 5, 2};
    // std::cout << "intro1\n";
    int counter = 0;
    int mdl_n = stoi(argv[argc - 1]);
    // std::cout << "intro2\n";
    int g = 0;

    for (const auto &entry : fs::directory_iterator(path))
    {
        // cout << "intro3\n";
        /*if(counter < mdl_n)
        {
            break;
        }*/
        // cout << "intro4\n";
        models.push_back(lang_model(entry.path(), k[g], alfa[g]));
        counter++;
        g++;
    }

    if (models.size() > (size_t)mdl_n)
    {
        cerr << "Model list inconsistent with <number of models used>\n";
        return -1;
    }

    string buffer;
    int model_idx = rand() % (int)models.size(); // first model; "randomly" chosen
    // cout << "intro5\n";
    // cout << model_idx << '\n';

    int j = 0;
    int cur_k = models[model_idx].get_k();
    // cout << cur_k << '\n';
    char storage = ' ';
    double prob;

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
    pair<int, int> presence;
    // cout <<"here1\n";

    while (!files.eof())
    {
        // cout <<"here2\n";
        while ((int)buffer.size() > cur_k - 1)
        {
            buffer.erase(buffer.begin());
            // cout << '.';
        }
        // cout << '\n';
        // cout <<"here3\n";
        while ((int)buffer.size() < cur_k - 1)
        {
            files.read(&storage, sizeof(char));
            buffer.push_back(storage);
            // cout << '-';
        }

        // cout << '\n';
        // cout <<"here4\n";
        files.read(&storage, sizeof(char));
        buffer.push_back(storage);

        prob -= log2(models[model_idx].model_find(buffer));

        for (int j = 0; j < (int)models.size(); j++)
        {
            // cout << '_';
            presence = models[j].check_presence(buffer);
            if (j != model_idx)
            {
                if (presence.first)
                {
                    if ((presence.second < low_size) || (models[model_idx].get_mstr() > models[j].get_mstr()))
                    {
                        low_size = presence.second;
                        model_idx = j;
                        cur_k = models[j].get_k();
                    }
                }
            }
        }
        // cout << '\n';
        buffer.erase(buffer.begin());
    }
    files.close();
    files.open(argv[argc - 2], ios::in);
    cout << "Number of bits needed: " << prob << '\n';

    for (int o = 0; o < mdl_n; o++)
    {
        prob = 0;
        while (!files.eof())
        {
            // cout <<"here2\n";
            // cout << '\n';
            // cout <<"here3\n";
            while ((int)buffer.size() < models[o].get_k() - 1)
            {
                files.read(&storage, sizeof(char));
                buffer.push_back(storage);
                // cout << '-';
            }

            // cout << '\n';
            // cout <<"here4\n";
            files.read(&storage, sizeof(char));
            buffer.push_back(storage);

            prob -= log2(models[o].model_find(buffer));
            // cout << '\n';
            buffer.erase(buffer.begin());
        }
        cout << "Using only model " << o << ", " << prob << " bits are needed\n";
        files.close();
        files.open(argv[argc - 2], ios::in);
    }
    return 0;
}
