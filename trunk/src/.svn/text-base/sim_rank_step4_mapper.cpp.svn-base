#include "util.h"

static const char sep = '\t';
static const char TAG_SIM = 'S';
static const char TAG_ADJ = 'A';

const static size_t MAX_N = 100;



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
        // data not from sim_table, from sim_rank_sim or count_self_sim
        if (!flag)
        {
            // take the first two objs as the key
            vector<string> vec = util::split('\t', data);
            string key(vec[0] + "\1" + vec[1]);
            std::cout << key << "\t" << vec[2] << "\t" << TAG_SIM << std::endl;
        }
        else
        {
            // format: obj1 \1 obj2 \t obj1_Neighbors \t obj2_Neighbors
            vector<string> vec = util::split('\t', data);
            if (vec.size() >= 3)
            {
                vector<string> left_neighbors = util::split(',', vec[1]);
                vector<string> right_neighbors = util::split(',', vec[2]);
                size_t ln_sz = left_neighbors.size();
                size_t rn_sz = right_neighbors.size();

                for(size_t i=0; i<ln_sz && i<MAX_N; ++i)
                {
                    for(size_t j=0; j<rn_sz && j<MAX_N; ++j)
                    {
                        string key(left_neighbors[i]);
                        key.append("\1");
                        key.append(right_neighbors[j]);
                        std::cout << key << "\t" << vec[0] << "\t" << TAG_ADJ << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}


void t()
{
    string data;
    while(getline(cin, data))
    {

        // format: obj1 \1 obj2 \t obj1_Neighbors \t obj2_Neighbors
        vector<string> vec = util::split('\t', data);
        if (vec.size() >= 3)
        {
            vector<string> left_neighbors = util::split(',', vec[1]);
            vector<string> right_neighbors = util::split(',', vec[2]);
            size_t ln_sz = left_neighbors.size();
            size_t rn_sz = right_neighbors.size();

            for(size_t i=0; i<ln_sz; ++i)
            {
                for(size_t j=0; j<rn_sz; ++j)
                {
                    string key(left_neighbors[i]);
                    key.append("\1");
                    key.append(right_neighbors[j]);
                    std::cout << key << "\t" << vec[0] << "\t" << TAG_ADJ << std::endl;
                }
            }
        }
    }
}


int main(int argc, char** argv)
{
    int ret = run();
    return ret;

}
