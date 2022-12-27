#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "math.h"
#include <fstream>
#include <algorithm>
#include <filesystem>

class lang_model
{
    private:
        int sigma;
        double a;
        std::map<std::string,std::map<char,double>> mdl;
        int k;
        double missing_str;
        std::string language;
    public:
        lang_model(std::string file_path, int order_k, double alfa)
        {
            std::ifstream model_input(file_path);
            std::string buffer,line,prob_str;
            std::map<char,double> temp;
            double probability;
            char c;

            language = file_path.substr(16,size(file_path)-26);

            k = order_k;
            a = alfa;

            getline(model_input,line);
            sigma = stod(line);
            missing_str = a/(a*sigma);

            while(getline(model_input,line))
            {
                temp.clear();
                buffer.clear();
                prob_str.clear();

                for(int i = 0 ; i < k ; i++)
                {
                    if(line[i] != '|')
                    {
                        buffer.push_back(line[i]);
                    }
                    else
                    {
                        buffer.push_back('\n');
                    }
                    
                }

                c = line[k];

                for(size_t i = k+1 ; i < size(line) ; i++)
                {
                    prob_str.push_back(line[i]);
                }


                probability = stod(prob_str);

                temp.insert(std::pair<char,double>(c,probability));
                mdl.insert(std::pair<std::string,std::map<char,double>>(buffer,temp));
            }
        }

        lang_model(std::string file_path, double alfa)
        {
            std::ifstream model_input(file_path);
            std::string buffer,line,prob_str;
            std::map<char,double> temp;
            double probability;
            char c;

            language = file_path.substr(16,size(file_path)-26);

            getline(model_input,line);
            k = stoi(line);
            a = alfa;

            getline(model_input,line);
            sigma = stod(line);
            missing_str = a/(a*sigma);

            while(getline(model_input,line))
            {
                temp.clear();
                buffer.clear();
                prob_str.clear();

                for(int i = 0 ; i < k ; i++)
                {
                    if(line[i] != '|')
                    {
                        buffer.push_back(line[i]);
                    }
                    else
                    {
                        buffer.push_back('\n');
                    }
                    
                }

                c = line[k];

                for(size_t i = k+1 ; i < size(line) ; i++)
                {
                    prob_str.push_back(line[i]);
                }


                probability = stod(prob_str);

                temp.insert(std::pair<char,double>(c,probability));
                mdl.insert(std::pair<std::string,std::map<char,double>>(buffer,temp));
            }
        }

        double model_find(std::string line)
        {
            std::string buffer;
            char c;

            std::map<char,double>::iterator inner;
            std::map<std::string,std::map<char,double>>::iterator outer;


            for(int i = 0 ; i < k ; i++)
            {
                buffer.push_back(line[i]);
            }
            c = line[k];
            outer = mdl.find(buffer);
            if(outer == mdl.end())
            {
                return missing_str;
            }
            else
            {
                inner = outer->second.find(c);
                if (inner == outer->second.end())
                {
                    return missing_str;
                }
                else
                {
                    return inner->second;
                }
            }
        }

        std::pair<int,int> check_presence(std::string line)
        {
            std::string buffer;
            char c;

            std::map<char,double>::iterator inner;
            std::map<std::string,std::map<char,double>>::iterator outer;


            for(int i = 0 ; i < k ; i++)
            {
                buffer.push_back(line[i]);
            }
            c = line[k];
            outer = mdl.find(buffer);
            if(outer == mdl.end())
            {
                return std::pair<int,int>(0,(int)mdl.size());
            }
            else
            {
                inner = outer->second.find(c);
                if (inner == outer->second.end())
                {
                    return std::pair<int,int>(0,(int)mdl.size());
                }
                else
                {
                    return std::pair<int,int>(1,(int)mdl.size());
                }
            }
        }

        std::string get_lang()
        {
            return language;
        }

        int get_sigma()
        {
            return sigma;
        }

        double get_mstr()
        {
            return missing_str;
        }

        int get_k()
        {
            return k;
        }

        int get_size()
        {
            return (int)mdl.size();
        }
    
};