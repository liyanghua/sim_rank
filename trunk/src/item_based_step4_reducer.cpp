#include  "BaseReducer.h"


const static char* TAG_USER_RATING = "R";
const static char* TAG_ITEM_SIM = "S";

class ItemBasedReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            // append the user-rating items to item-sim-matrix
            size_t sz = user_rating_vec.size();
            size_t isz = items_sim_vec.size();
            
            // output format: item1 \t item2 \t user_id \t score
            // which denotes P(user_id, item2)
            for(size_t i=0; i<isz; isz++)
            {
                const string& items_sim = items_sim_vec[i];
                // format: item \t sim
                vector<string> t1 = util::split('\t', items_sim);
                float sim = atof(t1[1].c_str());
                const string& item1 = t1[0];
                for(size_t j=0; j<sz; j++)
                {
                    const string& user_rating_str = user_rating_vec[j];
                    vector<string> v = util::split('\t', user_rating_str);
                    const string& user = v[0];
                    float score = atof(v[1].c_str());
                    float s = sim * score;

                    std::cout << m_preKey << "\t" << item1 << "\t" << user << "\t" << s << std::endl;
                }
            }

            return true;
        }
        
        virtual bool AddLine(const string& value)
        {
            if (!value.empty())
            {
                vector<string>  v = util::split('\t', value);
                size_t sz = v.size();
                const string& tag = v[sz - 1];
                // user rating
                if (tag.compare(TAG_USER_RATING) == 0)
                {
                    user_rating_vec.push_back(value);
                }
                else if (tag.compare(TAG_ITEM_SIM) == 0) // item-item sim
                {
                    items_sim_vec.push_back(value);
                }
            }
            
            return true;
        }

        virtual bool Reset()
        {
            user_rating_vec.clear();
            items_sim_vec.clear();

            return true;
        }

    private:
        vector<string> user_rating_vec;
        vector<string> items_sim_vec;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new ItemBasedReducer();
    br->Run();

    delete br;

    return 0;
}
