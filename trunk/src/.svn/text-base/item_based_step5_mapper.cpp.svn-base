#include "util.h"

#define __DEBUG__

static const char sep = '\t';



int run()
{
	std::string data;
    vector<string> vec;
	while (getline(cin, data))
    {
        vec = split(sep, data);
        // format: item1 \t item2 \t user_id \t score
        const string& item_id = vec[1];
        const string& user_id = vec[2];
        const string& score = vec[3];
            
        // user and item as the key
        std::cout << user_id << "\1" << item_id << "\t" << score << std::endl;
    }
    
    return 0;
}

int main(int argc, char** argv)
{
    int ret = run();
    return ret;
}
