#include  "BaseReducer.h"

class GeneralReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            // item list
            size_t sz = m_dataVec.size();
            if (sz == 0)
            {
                return true;
            }
            size_t last = sz - 1;
            std::cout << m_preKey << "\t";
            
            for(size_t i=0; i<sz; ++i)
            {
                std::cout << m_dataVec[i].c_str();
                if (i != last)
                {
                    std::cout << ",";
                }
            }
            std::cout << endl;

            return true;
        }
};


int main(int argc, char** argv)
{
    BaseReducer* br = new GeneralReducer();
    br->Run();

    delete br;

    return 0;
}
