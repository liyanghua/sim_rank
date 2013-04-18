#include  "BaseReducer.h"

static const char* TAG_SIM = "S";
static const char* TAG_ADJ = "A";

static size_t const MAX_N = 5000;

class SimRankReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            // append the ajs to the sim
            size_t sz = sim_vec.size();
            for(size_t i=0; i<sz; ++i)
            {
                std::cout << m_preKey << "\t" << sim_vec[i] <<"\t" << adjs << std::endl;
                
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
                if (tag.compare(TAG_SIM) == 0 && sim_vec.size() < MAX_N)
                {
                    sim_vec.push_back(value);
                }
                else if (tag.compare(TAG_ADJ) == 0)
                {
                    adjs = value;
                }
            }
            
            return true;
        }

        virtual bool Reset()
        {
            sim_vec.clear();
            adjs.clear();

            return true;
        }

    private:
        vector<string> sim_vec;
        string adjs;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new SimRankReducer();
    br->Run();

    delete br;

    return 0;
}
