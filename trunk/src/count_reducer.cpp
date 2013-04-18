#include  "BaseReducer.h"

class GeneralReducer : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            std::cout << m_preKey << "\t" << m_preKey << "\t" << 1 << endl;
            return true;
        }

        virtual bool AddLine(const string& value)
        {
            if (!value.empty())
            {
                N += atoi(value.c_str());
            }

            return true;
        }

        virtual bool Reset()
        {
            N = 0;
            return true;
        }

    private:
        int N;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new GeneralReducer();
    br->Run();

    delete br;

    return 0;
}
