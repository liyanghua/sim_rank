#include "util.h"

namespace util
{
    bool load_file_to_vector(const char* file, vector<Record<string,string,int> >& data, char sep)
    {
        if (NULL == file)
        {
            std::cerr << "File can not be empty!" << std::endl;
            return false;
        }
        fstream fs;
        fs.open(file);
        if (!fs.is_open())
        {
            std::cerr << "Can not open file:" << file << std::endl;
            return false;
        }
        string line;
        while(getline(fs, line))
        {
            // comments
            if(line.empty() || line[0] == '#')
            {
                continue;
            }
            vector<string> vec = util::split(sep, line);
            size_t sz = vec.size();
            if (sz >= 3)
            {
                Record<string, string, int> r;
                r.obj1 = vec[0];
                r.obj2 = vec[1];
                r.action = atoi(vec[2].c_str());
                data.push_back(r);
            }
        }
        fs.close();

        return true;
    }
    bool load_file_to_vector(const char* file, vector<DataInfo> & data, char sep)
    {
        if (NULL == file)
        {
            std::cerr << "File can not be empty!" << std::endl;
            return false;
        }
        fstream fs;
        fs.open(file);
        if (!fs.is_open())
        {
            std::cerr << "Can not open file:" << file << std::endl;
            return false;
        }
        string line;
        while(getline(fs, line))
        {
            // comments
            if(line.empty() || line[0] == '#')
            {
                continue;
            }
            vector<string> vec = util::split(sep, line);
            size_t sz = vec.size();
            if (sz >= 3)
            {
                // format: user_id,item_id,rating
                DataInfo di;
                di.user_id = atoi(vec[0].c_str());
                di.item_id = atoi(vec[1].c_str());
                di.rating = atof(vec[2].c_str());
                data.push_back(di);
            }
        }
        fs.close();

        return true;
    }

    void print_vec(vector<DataInfo> & data)
    {
        size_t sz = data.size();
        for(size_t i=0; i<sz; ++i)
        {
            DataInfo& d = data[i];
            d.print();
        }
    }

    void print_vec(vector<Record<string, string, int> > & data)
    {
        size_t sz = data.size();
        for(size_t i=0; i<sz; ++i)
        {
            Record<string, string, int>& d = data[i];
            d.print();
        }
    }
};
