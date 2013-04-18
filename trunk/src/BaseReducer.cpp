#include "BaseReducer.h"

void BaseReducer::Run()
{
    m_dataVec.reserve(m_initReserveSize);

    string cur_key;
    string data;
    while (getline(cin, data))
    {
        if (data.empty())
        {
            continue;
        }

        size_t pos = data.find(TAB);
        if (pos == string::npos)
        {
            continue;
        }

        cur_key = data.substr(0, pos);
        string cur_info = data.substr(pos + 1);
        if (cur_key == m_preKey)
        {
            AddLine(cur_info);
        }
        else
        {
            if (!m_preKey.empty())
            {
                Flush();
                Reset();
            }
            AddLine(cur_info);
            m_preKey = cur_key;
        }
    }

    if (!m_preKey.empty())
    {
        Flush();
        Reset();
    }

    // release the memory
    vector<string>().swap(m_dataVec);

}

void BaseReducer::FlushDefault() 
{
    size_t sz = m_dataVec.size();
    if (sz == 0)
    {
        return;
    }
    std::cout << m_preKey;
    for (size_t i=0; i<sz; ++i)
    {
        cout << TAB << m_dataVec[i];
    }

    cout << endl;
}

