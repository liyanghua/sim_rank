#include  "BaseReducer.h"

class ItemBasedReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            run();
            return true;
        }

    private:
        void run()
        {
            // item list
            size_t sz = m_dataVec.size();
            std::cout << m_preKey << "\t" << sz << std::endl;
#if 0
            for(size_t i=0; i<sz; ++i)
            {
                for(size_t j=0; j<sz; ++j)
                {
                    std::cout << m_dataVec[i] << "\t" << m_dataVec[j] << std::endl;
                }
            }
#endif
        }
};


int main(int argc, char** argv)
{
    BaseReducer* br = new ItemBasedReducer();
    br->Run();

    delete br;

    return 0;
}
