#include "util.h"

static const char sep = '\t';
static const char TAG_SIM = 'S';
static const char TAG_ADJ = 'A';

int run()
{
	std::string data;
    vector<string> vec;
    char* input_file = getenv("map_input_file");
    char* file_flag = getenv("file_flag");
    
    bool flag = false;
    char * result = strstr(input_file, file_flag);
    flag = (NULL != result);
    

	while (getline(cin, data))
    {
        // data from step1
        if (flag)
        {
            // take the first two objs as the key
            vector<string> vec = util::split('\t', data);
            string key(vec[0] + "\1" + vec[1]);
            std::cout << key;
            size_t sz = vec.size();
            for(size_t i=2; i<sz; i++)
            {
                std::cout << "\t" << vec[i];
            }
            std::cout << endl;
        }
        else
        {
            vector<string> vec = util::split('\t', data);
            std::cout << vec[1] << "\1" << vec[0];
            for(size_t i=2; i<vec.size(); ++i)
            {
                std::cout << "\t" << vec[i];
            }
            std::cout << "\tR" << endl;
        }
    }

    return 0;
}


int main(int argc, char** argv)
{
    int ret = run();
    return ret;
}
