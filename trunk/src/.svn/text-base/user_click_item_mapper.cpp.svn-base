#include "util.h"
#include "strnormalize.h"

int main(int argc, char** argv)
{
	std::string data;
    vector<string> vec;

//        string& nid_cat = vec[19];    
	while (getline(cin, data))
    {
        vec = split(TAB, data);
        string& user_id = vec[3];
        string& nid = vec[27];
        if (user_id == "0" || user_id == "_")
        {
            continue;
        }

        std::cout << user_id << "\1" << nid << "\t" << 1 << std::endl;
	}

    return 0;
}
