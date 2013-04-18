#include  "BaseReducer.h"


class QueryDocClick : public BaseReducer
{
    public:
        virtual bool Flush()
        {
            // key is query \1 doc
            vector<string> vec = util::split('\1', m_preKey);
            if (vec.size() == 2 && N < 1000000)
            {
                std::cout << vec[0] << "," << vec[1] << "," << N << std::endl;
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
    BaseReducer* br = new QueryDocClick();
    br->Run();

    delete br;

    return 0;
}
