#include  "BaseReducer.h"

class ItemBasedReducer : public BaseReducer
{
    public:
        ItemBasedReducer() : score(0.f) {}
    public:
        virtual bool Flush()
        {
            vector<string> v = util::split('\1', m_preKey);
            std::cout << v[0] << "\t" << v[1] << "\t" << score << std::endl;

            return true;
        }
        
        virtual bool AddLine(const string& value)
        {
            if (!value.empty())
            {
                score += atof(value.c_str());
            }
            
            return true;
        }

        virtual bool Reset()
        {
            score = 0.f;
            return true;
        }

    private:
        float score;
};


int main(int argc, char** argv)
{
    BaseReducer* br = new ItemBasedReducer();
    br->Run();

    delete br;

    return 0;
}
