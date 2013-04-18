#include  "BaseReducer.h"

typedef std::tr1::unordered_map<string ,int> ITEM_2_N_MAP;
typedef ITEM_2_N_MAP::iterator ITEM_2_N_MAP_IT;

class ItemBasedReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            ITEM_2_N_MAP_IT it = item_map.begin();
            for(; it != item_map.end(); it++)
            {
                std::cout << m_preKey << "\t" << it->first << "\t" << it->second << std::endl;
            }

            return true;
        }
        
        virtual bool AddLine(const string& value)
        {
            if (!value.empty())
            {
                item_map[value] += 1;
            }
            
            return true;
        }

        virtual bool Reset()
        {
            item_map.clear();
            return true;
        }

    private:
        ITEM_2_N_MAP item_map;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new ItemBasedReducer();
    br->Run();

    delete br;

    return 0;
}
