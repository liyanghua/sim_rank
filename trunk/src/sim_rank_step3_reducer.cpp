#include  "BaseReducer.h"

class SimRankReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            format();

            return true;
        }

    private:
        void naive_output()
        {
            size_t sz = m_dataVec.size();
            std::cout << m_preKey;
            for(size_t i=0; i<sz; ++i)
            {
                std::cout << "\t" << m_dataVec[i];
            }

            std::cout << endl;
        }

        void format()
        {
            size_t sz = m_dataVec.size();
            if (sz == 2)
            {
                const string& s1 = m_dataVec[0];
                const string& s2 = m_dataVec[1];
                vector<string> vec1 = util::split('\t', s1);
                vector<string> vec2 = util::split('\t', s2);
                size_t s = vec1.size();
                const string& tag = vec1[s - 1];
                if (tag.compare("R") == 0)
                {
                    // format:sim_score \t S \t adjs \t A
                    const string& first_adj = vec2[2];
                    // format:sim_score \t S \t adjs \t A \t R
                    const string& second_adj =vec1[2];
                    std::cout << m_preKey << "\t" << first_adj << "\t" << second_adj << std::endl;
                }
                else
                {
                    const string& first_adj = vec1[2];
                    const string& second_adj = vec2[2];
                    std::cout << m_preKey << "\t" << first_adj << "\t" << second_adj << std::endl;
                }
            }
        }
        
};


int main(int argc, char** argv)
{
    BaseReducer* br = new SimRankReducer();
    br->Run();

    delete br;

    return 0;
}
