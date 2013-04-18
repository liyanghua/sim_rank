#include "util.h"

#define __DEBUG__

static const char sep = ',';



int run()
{
	std::string data;
    vector<string> vec;
	while (getline(cin, data))
    {
        vec = split(sep, data);
        const string& first_obj = vec[0];
        const string& second_obj = vec[1];

        std::cout << first_obj << TAB << second_obj << std::endl;

        // swap them
        std::cout << second_obj << TAB << first_obj << std::endl;
    }
    
    return 0;
}

int main(int argc, char** argv)
{
    int ret = run();
    return ret;
}
