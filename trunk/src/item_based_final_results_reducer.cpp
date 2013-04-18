#include  "BaseReducer.h"

struct ItemScore
{
    int item_id;
    float score;
};

bool sort_fun(const ItemScore& l, const ItemScore& r)
{
    return l.score > r.score;
}

typedef std::tr1::unordered_map<int, float> ITEM_MAP;
typedef ITEM_MAP::iterator ITEM_MAP_IT;

class ItemBasedReducer : public BaseReducer
{
    public:
        ItemBasedReducer(int top_N_) : top_N(top_N_) {}
    public:
        virtual bool Flush()
        {
            vector<ItemScore> vec;
            vec.reserve(top_N * 2);
            ITEM_MAP_IT it = item_score_map.begin();

            ItemScore is;
            for(; it != item_score_map.end(); ++it)
            {
                is.item_id = it->first;
                is.score = it->second;
                vec.push_back(is);
            }


            std::sort(vec.begin(), vec.end(), sort_fun);

            size_t sz = vec.size();
            for(size_t i=0; i<sz; ++i)
            {
                std::cout << m_preKey << "\t" << vec[i].item_id << "\t" << vec[i].score << std::endl;
            }
            
            return true;
        }
        
        virtual bool AddLine(const string& value)
        {
            // format: item \t score
            if (!value.empty())
            {
                vector<string> v = util::split('\t', value);
                if (v.size() >= 2)
                {
                    const string& item_id = v[0];
                    int item_id_num = atoi(item_id.c_str());
                    float score = atof(v[1].c_str());
                    item_score_map[item_id_num] = score;
                }
            }
            
            return true;
        }

        virtual bool Reset()
        {
            item_score_map.clear();
            return true;
        }

    private:
        ITEM_MAP item_score_map;
        int top_N;
};


int main(int argc, char** argv)
{
    int top_N = 5;
    if (argc >= 2)
    {
        top_N = atoi(argv[1]);
    }
    BaseReducer* br = new ItemBasedReducer(top_N);
    br->Run();

    delete br;

    return 0;
}
