#ifndef __ITEM_BASED_COMMON_H__
#define __ITEM_BASED_COMMON_H__

#include <set>
#include <map>
#include "util.h"

namespace item_based
{
    struct ItemScore
    {
        int item_id;
        float score;
    };

    class ItemBasedDriver
    {
        public:
            bool build_inverted_dict(const vector<DataInfo> & data_vec);
            void print_inverted_dict();
            void build_item_2_item_co_map();
            // give recommendation to user
            bool run(int user_id, vector<ItemScore>& recommend_items);


        private:
            std::tr1::unordered_map<int, vector<int> > item_user_num_map;
            std::vector<int> item_list;
            map<int, map<int, int> > item_2_item_co_map;
            map<int, map<int, float> > user_2_item_rating_map;
    };
};

#endif //__ITEM_BASED_COMMON_H__

