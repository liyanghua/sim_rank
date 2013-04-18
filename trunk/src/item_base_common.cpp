#include <algorithm>
#include "item_base_common.h"

#define __DEBUG__

bool sort_fun(int i, int j)
{
    return i<j;
}

static bool get_interset(vector<int>& left, vector<int>& right, vector<int> & out)
{
    vector<int>::iterator it1 = left.begin();
    vector<int>::iterator it2 = right.begin();
    while(it1 != left.end() && it2 != right.end())
    {
        if (*it1 < *it2) it1++;
        else if (*it2 < *it1) it2++;
        else
        {
            out.push_back(*it1);
            it1++;
            it2++;
        }
    }

    return true;
}

namespace item_based
{
    typedef std::tr1::unordered_map<int, vector<int> >::iterator MAPIT;

    bool ItemBasedDriver::build_inverted_dict(const vector<DataInfo>& data_vec)
    {
        size_t sz = data_vec.size();
        for(size_t i=0; i<sz; ++i)
        {
            // user_id, item_id, rating
            const DataInfo& d = data_vec[i];
            vector<int> & l = item_user_num_map[d.item_id];
            if (std::find(l.begin(), l.end(), d.user_id)
                    != l.end())
            {
                continue;
            }
            l.push_back(d.user_id);

            if (std::find(item_list.begin(), item_list.end(), d.item_id) == item_list.end())
            {
                item_list.push_back(d.item_id);
            }

            user_2_item_rating_map[d.user_id][d.item_id] = d.rating;
        }
        // sort the item_list
        std::sort(item_list.begin(), item_list.end(), sort_fun);

        for(size_t i=0; i<item_list.size(); ++i)
        {
            vector<int>& l = item_user_num_map[item_list[i]];
            std::sort(l.begin(), l.end(), sort_fun);
        }

        return true;
    }

    void ItemBasedDriver::print_inverted_dict()
    {
        MAPIT it = item_user_num_map.begin();
        for (; it != item_user_num_map.end(); ++it)
        {
            const vector<int> & s = it->second;
            std::cout << it->first << "->";
            vector<int>::const_iterator set_it = s.begin();
            for(; set_it != s.end(); ++set_it)
            {
                std::cout << *set_it << "\t";
            }
            std::cout << endl;
        }

        std::cout << endl;
        for(size_t i=0; i<item_list.size(); ++i)
        {
            std::cout << item_list[i] << "\t";
        }
        std::cout << endl;

        std::cout << "item_2_item co map" << std::endl;

        map<int, map<int, int> >::iterator xit = item_2_item_co_map.begin();
        map<int, int>::iterator mit;
        for(; xit != item_2_item_co_map.end(); ++xit)
        {
            int item_id = xit->first;
            map<int, int>& item_n = xit->second;
            std::cout << item_id << ":";
            for(mit = item_n.begin(); mit != item_n.end(); ++mit)
            {
                std::cout << "(" << mit->first << "," << mit->second << ")\t";
            }
            std::cout << endl;
        }
    }

    void ItemBasedDriver::build_item_2_item_co_map()
    {
        size_t sz = item_list.size();
        vector<int> interset;
        vector<int>::iterator it;
        for(size_t i=0; i<sz; ++i)
        {
            int left_item = item_list[i];
            vector<int>& left = item_user_num_map[left_item];
            item_2_item_co_map[left_item][left_item] = left.size();
            for(size_t j=i+1; j<sz; j++)
            {
                int right_item = item_list[j];
                vector<int>& right = item_user_num_map[right_item];
                get_interset(left, right, interset);
#ifdef __DEBUG__
                for(it =interset.begin(); it != interset.end(); ++it)
                {
                    std::cout << *it << "\t";
                }
                std::cout << endl;
#endif
                item_2_item_co_map[left_item][right_item] = item_2_item_co_map[right_item][left_item] = interset.size();
                interset.clear();
            }
        }
    }

    bool cmp_fun(const ItemScore& l, const ItemScore& r)
    {
        return l.score > r.score;
    }

    bool ItemBasedDriver::run(int user_id, vector<ItemScore>& recommend_items)
    {
        map<int, map<int, float> >::iterator it = user_2_item_rating_map.find(user_id);
        // user has no history items...
        if (it == user_2_item_rating_map.end())
        {
            return false;
        }
        map<int, float> & history_rating = it->second;
#ifdef __DEBUG__
        std::cout << "History rating for user:" << user_id << std::endl;
        map<int, float>::iterator xit = history_rating.begin();
        for(; xit != history_rating.end(); ++xit)
        {
            std::cout << "Item Id:" << xit->first << "," << "rating:" << xit->second << std::endl;
        }
#endif
        size_t item_sz = item_list.size();
        for(size_t i=0; i<item_sz; ++i)
        {
            float s = 0.f;
            int id_1 = item_list[i];
#ifdef __DEBUG__
            std::cout << "Check item:" << id_1 << std::endl;
#endif
#if 0
            if (history_rating.find(id_1) != history_rating.end())
            {
                continue;
            }
#endif
            
            for(size_t j=0; j<item_sz; ++j)
            {
                int id_2 = item_list[j];
                if (history_rating.find(id_2) == history_rating.end())
                {
                    continue;
                }
                s += item_2_item_co_map[id_1][id_2] * history_rating[id_2];
            }
            ItemScore is;
            is.item_id = id_1;
            is.score = s;
#ifdef __DEBUG__
            std::cout << "item,score:" <<id_1 <<"," << s << std::endl;
#endif
            recommend_items.push_back(is);
        }

        std::sort(recommend_items.begin(), recommend_items.end(), cmp_fun);
        return true;
    }
};
