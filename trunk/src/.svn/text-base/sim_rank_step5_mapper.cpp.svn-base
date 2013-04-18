#include "util.h"

static const char sep = '\t';
static const char TAG_V = 'V';

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
        // data from last_step, just output
        if (flag)
        {
            // format: obj1 \1 obj2 \t tmp_score
            std::cout << data << endl;
        }
        else
        {
            // format: obj1 \1 obj2 \t obj1_Neighbors \t obj2_Neighbors
            vector<string> vec = util::split('\t', data);
            if (vec.size() >= 3)
            {
                vector<string> left_neighbors = util::split(',', vec[1]);
                vector<string> right_neighbors = util::split(',', vec[2]);
                float ln_sz = static_cast<float>(left_neighbors.size());
                float rn_sz = static_cast<float>(right_neighbors.size());
                float C = 0.8;
                float V = C / (ln_sz * rn_sz);

                std::cout << vec[0] << "\t" << V << "\t" << TAG_V << std::endl;
            }
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    int ret = run();
    return ret;

}
