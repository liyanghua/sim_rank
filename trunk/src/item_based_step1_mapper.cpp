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
        // format: user_id, item_id, rating
        const string& user_id = vec[0];
        const string& item_id = vec[1];

        std::cout << user_id << TAB << item_id << std::endl;
    }
    
    return 0;
}

int main(int argc, char** argv)
{
    int ret = run();
    return ret;
}
