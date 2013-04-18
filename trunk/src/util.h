#ifndef __UTIL_HPP_
#define __UTIL_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tr1/unordered_map>

#include "StringUtils.h"
#include "StrUtils.h"

using namespace std;
using namespace util;


#define CTRL_V_A '\1'
#define CTRL_V_B '\2'

#define TAB '\t'


namespace util
{
    struct DataInfo
    {
        int user_id;
        int item_id;
        float rating;
        void print()
        {
            std::cout << user_id << "\t" << item_id << "\t" << rating << std::endl;
        }
    };
    template<typename obj1_type, typename obj2_type, typename action_type>
        struct Record
        {
            obj1_type obj1;
            obj2_type obj2;
            action_type action;
            void print()
            {
                std::cout << obj1 << "\t" << obj2 << "\t" << action << std::endl;
            }
        };
    bool load_file_to_vector(const char* file, vector<DataInfo> & data, char sep);
    bool load_file_to_vector(const char* file, vector<Record<string,string,int> >& data, char sep);
    void print_vec(vector<DataInfo> & data);
    void print_vec(vector<Record<string, string, int> >& data);
};

#endif //__UTIL_HPP_
