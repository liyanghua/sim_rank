#include  "BaseReducer.h"


class QueryDocClick : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            int sz = static_cast<int>(m_dataVec.size());
            int f_sz = sz;

            for(int i=0;i<f_sz;++i)
            {
                for(int j=i+1; j<f_sz; ++j)
                {
                    if (m_dataVec[i].compare(m_dataVec[j]) == 0)
                    {
                        continue;
                    }

                    std::cout << m_dataVec[i] << "\t" << m_dataVec[j] << "\t" << 0 << std::endl;
                }
            }
            
            return true;
        }
};


int main(int argc, char** argv)
{
    BaseReducer* br = new QueryDocClick();
    br->Run();

    delete br;

    return 0;
}
