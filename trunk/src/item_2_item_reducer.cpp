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
        }
};


int main(int argc, char** argv)
{
    BaseReducer* br = new ItemBasedReducer();
    br->Run();

    delete br;

    return 0;
}
