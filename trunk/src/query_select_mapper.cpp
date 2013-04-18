#include "util.h"


int main(int argc, char** argv)
{
	std::string data;
    vector<string> vec;

	while (getline(cin, data))
    {
        vec = split(',', data);
        if (vec.size() >= 2)
        {
            // nid \t query
            std::cout << vec[1] << "\t" << vec[0] << std::endl;
        }
    }

    return 0;
}
