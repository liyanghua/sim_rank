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
        // data from sim
        if (flag)
        {
            // format: obj1,obj2,sim
            vector<string> vec = util::split('\t', data);
            // filter the same obj
            if (vec[0].compare(vec[1]) == 0)
            {
                continue;
            }
            for(size_t i=0; i<vec.size(); ++i)
            {
                std::cout << vec[i] << "\t";
            }
            std::cout << TAG_SIM << std::endl;
        }
        else
        {
            // format: obj1 \t adjs(sep by comma)
            std::cout << data << sep << TAG_ADJ << std::endl;
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    int ret = run();
    return ret;
}
