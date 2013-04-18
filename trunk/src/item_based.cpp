#include "util.h"
#include "item_base_common.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage:" << argv[0] << ", file" << std::endl;
        return -1;
    }
    vector<DataInfo> vec;
    char sep(',');
    bool ret = util::load_file_to_vector(argv[1], vec, sep);
    if (!ret)
    {
        return -1;
    }
    print_vec(vec);

    item_based::ItemBasedDriver driver;
    driver.build_inverted_dict(vec);
    driver.build_item_2_item_co_map();
    driver.print_inverted_dict();
    using item_based::ItemScore;

    for(int user_id = 1; user_id <=5; user_id++)
    {
        vector<ItemScore> recommend_list;
        driver.run(user_id, recommend_list);

        std::cout << "Recommend items for user:" << user_id << std::endl;
        for(size_t i=0; i<recommend_list.size(); ++i)
        {
            std::cout << recommend_list[i].item_id << "\t" << recommend_list[i].score << std::endl;
        }
        std::cout << endl;
    }

    return 0;
}
