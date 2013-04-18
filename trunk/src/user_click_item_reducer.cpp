#include  "BaseReducer.h"


class UserItemClick : public BaseReducer
{
    public:
        UserItemClick() : N(0) {}
    public:
        virtual bool Flush()
        {
            vector<string> vec = util::split('\1', m_preKey);
            if (vec.size() == 2)
            {
                std::cout << vec[0] << "\t" << vec[1] << "\t" << N << std::endl;
            }

            return true;
        }
        
        virtual bool AddLine(const string& value)
        {
            int n = atoi(value.c_str());
            N += n;

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
    BaseReducer* br = new UserItemClick();
    br->Run();

    delete br;

    return 0;
}
