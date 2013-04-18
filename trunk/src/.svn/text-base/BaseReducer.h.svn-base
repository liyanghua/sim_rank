#ifndef __BASE_REDUCER_H__
#define __BASE_REDUCER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

#include <tr1/unordered_map>
#include <map>

#include "StringUtils.h"

using namespace std;
using namespace util;

#define CTRL_V_A '\1'
#define CTRL_V_B '\2'
#define TAB '\t'
#define SPACE ' '

static const int MSIZE = 64;


// A simple template method design pattern
class BaseReducer
{
    public:
        BaseReducer() : m_preKey(""), m_initReserveSize(MSIZE) { m_dataVec.clear(); }
        virtual ~BaseReducer() {}
        
        // The template method
        void Run();

    protected:
        // the default implementation 
        virtual bool AddLine(const string& value) { m_dataVec.push_back(value); return true; }
        virtual bool Flush() { FlushDefault(); return true;}
        virtual bool Reset() { m_dataVec.clear(); return true; }

        void FlushDefault();
        string m_preKey;
        vector<string> m_dataVec;

        size_t m_initReserveSize;
};

#endif // __BASE_REDUCER_H__
