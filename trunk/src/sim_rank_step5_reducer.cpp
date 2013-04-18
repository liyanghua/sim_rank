#include  "BaseReducer.h"

static const char* TAG_V = "V";

class SimRankReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            float final_score = S * V;
            vector<string> vec = util::split('\1', m_preKey);
            if (vec.size() == 2)
            {
                // update the final sim score
                std::cout << vec[0] << "\t" << vec[1] << "\t" << final_score;
            }

            std::cout << endl;
            
            return true;
        }

        virtual bool AddLine(const string& value)
        {
            if (!value.empty())
            {
                vector<string>  v = util::split('\t', value);
                size_t sz = v.size();
                const string& tag = v[sz - 1];
                if (tag.compare(TAG_V) == 0)
                {
                    // format: obj1 \1 obj2 \t sim_score \t TAG_SIM
                    V = atof(v[0].c_str());

                }
                else
                {
                    // format: obj1 \t obj2 \t s
                    float s = atof(v[0].c_str());
                    S += s;

                }
            }

            return true;
        }

        virtual bool Reset()
        {
            V = 0.f;
            S = 0.f;

            return true;
        }

    private:
        float S;
        float V;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new SimRankReducer();
    br->Run();

    delete br;

    return 0;
}
