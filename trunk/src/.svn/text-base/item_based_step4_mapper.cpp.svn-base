#include "util.h"

static const char sep = '\t';
const static char* TAG_USER_RATING = "R";
const static char* TAG_ITEM_SIM = "S";

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
        if (flag)
        {
            std::cout << data << "\t" << TAG_USER_RATING << std::endl;
        }
        else
        {
            std::cout << data << "\t" << TAG_ITEM_SIM << std::endl;
        }
    }
    
    return 0;
}

int main(int argc, char** argv)
{
    int ret = run();
    return ret;
}
