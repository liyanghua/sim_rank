#include  "BaseReducer.h"

static const char* TAG_SIM = "S";
static const char* TAG_ADJ = "A";

class SimRankReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            std::vector<string> pair = util::split('\1', m_preKey);
            if (pair.size() == 2)
            {
                const string& obj1 = pair[0];
                const string& obj2 = pair[1];
                bool is_self = (obj1.compare(obj2) == 0);

                // compute the score
                size_t sz = neighbor_vec.size();
                for(size_t i=0; i<sz; ++i)
                {
                    std::cout << neighbor_vec[i];
                    if (is_self)
                    {
                        std::cout << "\t" << 1 << endl;
                    }
                    else
                    {
                        std::cout << "\t" << sim_score << endl;
                    }

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
                if (tag.compare(TAG_SIM) == 0)
                {
                    // format: obj1 \1 obj2 \t sim_score \t TAG_SIM
                    sim_score = atof(v[0].c_str());

                }
                else if (tag.compare(TAG_ADJ) == 0)
                {
                    // format: obj1 \t obj2 \t pair \t TAG
                    const string& pair = v[0];
#ifdef __DEBUG__
                    std::cout << "add pair:" << pair << std::endl;
#endif
                    neighbor_vec.push_back(pair);

                }
            }

            return true;
        }

        virtual bool Reset()
        {
            sim_score = 0;
            neighbor_vec.clear();

            return true;
        }

    private:
        vector<string> neighbor_vec;
        float sim_score;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new SimRankReducer();
    br->Run();

    delete br;

    return 0;
}
