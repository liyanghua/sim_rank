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
    
    // To check the data from user rating
    bool flag = false;
    char * result = strstr(input_file, file_flag);
    flag = (NULL != result);
    

	while (getline(cin, data))
    {
        // data from sim
        if (flag)
        {
            // format: obj1 \t obj2 \t sim, in reserve order
            vector<string> vec = util::split('\t', data);
            // filter the same obj
            if (vec[0].compare(vec[1]) == 0)
            {
                continue;
            }
            std::cout << vec[1] << "\t" << vec[0] << "\t" << vec[2] << "\t" << TAG_SIM << std::endl;
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
