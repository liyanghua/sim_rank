#include "util.h"
#include "strnormalize.h"

static const int first_level_cat = 16;
static const int leaf_cat = 50010850;

int main(int argc, char** argv)
{
	std::string data;
    vector<string> vec;
    
	while (getline(cin, data))
    {
        vec = split(TAB, data);
        string& query = vec[1];
//        string& user_id = vec[3];
        
        query = util::strip(query);
        if (query.empty())
        {
            continue;
        }
        strnormalize_utf8(query);

        string& nid = vec[27];
        int nid_cat = atoi(vec[19].c_str());
        // 女装
        if (nid_cat == leaf_cat)
        {
            std::cout << query << "\1" << nid << "\t" << 1 << std::endl;
        }
	}

    return 0;
}
