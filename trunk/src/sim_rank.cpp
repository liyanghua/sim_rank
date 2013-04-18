#include <map>
#include "util.h"

//#define __DEBUG__


// for undirect graph
template<class T1, class T2, class T3>
void build_adjacency_table(const vector<Record<T1, T2, T3> >& vec, 
        map<T1, map<T2, T3> >& adjacency_table, vector<T1>& left_vec, vector<T2>& right_vec)
{
    size_t sz = vec.size();
    for(size_t i=0; i<sz; ++i)
    {
        const Record<T1, T2, T3>& r = vec[i];
        adjacency_table[r.obj1][r.obj2] = r.action;
        adjacency_table[r.obj2][r.obj1] = r.action;
        if (std::find(left_vec.begin(), left_vec.end(), r.obj1) == left_vec.end())
        {
            left_vec.push_back(r.obj1);
        }

        if (std::find(right_vec.begin(), right_vec.end(), r.obj2) == right_vec.end())
        {
            right_vec.push_back(r.obj2);
        }
    }
}

typedef map<string, map<string, float> > LIST_MAP;
typedef LIST_MAP::iterator LIST_IT;


void print_sim_map(map<string, map<string, float> >& sim_table)
{
    std::cout << "+++++sim map++++" << std::endl;

    map<string, map<string, float> >::iterator it = sim_table.begin();
    for(; it != sim_table.end(); ++it)
    {
        map<string, float> & m = it->second;
        map<string, float> ::iterator xit = m.begin();
        std::cout << it->first << "->";
        for(; xit != m.end(); ++xit)
        {
            std::cout << "(" << xit->first << "," << xit->second << ")\t";
        }
        std::cout << endl;
    }

    std::cout << "+++++++sim map end++++" << std::endl;
    
}

float sim(map<string, map<string, float> >& sim_table, const string& n1, const string& n2)
{
    if (n1 == n2)
    {
        return 1.;
    }

    LIST_IT it = sim_table.find(n1);
    if (it == sim_table.end())
    {
        return 0;
    }

    map<string, float>& m = it->second;
    map<string, float>::iterator xit = m.find(n2);
    if (xit == m.end())
    {
        return 0;
    }

    return m[n2];
}

static const float C = 0.8;

// sim_rank(node_x,node_y) = {C/N(node_x)N(node_y)}sum(sum(sim_rank(i,j))) for i in E(node_x) and for j in E(node_y)
// in which N(x) denots the number of the neighbors of x
// and E(x) denots the set of neighbors of x
float run_sim_rank(map<string, map<string, int> >& list, 
        const string& node_x, const string& node_y,
        map<string, map<string, float> >& sim_table)
{
    typedef map<string, int>::iterator XIT;

    float sim_rank_score = 0.f;

    // no neighbors for node_x
    map<string, map<string, int> >::iterator it = list.find(node_x);
    if (it == list.end())
    {
        return 0;
    }
    map<string, int>& m1 = it->second;
    int N_X = m1.size();
    // no neighbors for node_y
    it = list.find(node_y);
    if (it == list.end())
    {
        return 0;
    }
    map<string, int>& m2 = it->second;
    int N_Y = m2.size();
#ifdef __DEBUG__
    std::cout << "N_X:" << N_X << ", N_Y:" << N_Y << std::endl;
#endif
    XIT mit = m1.begin();
    for(; mit != m1.end(); ++mit)
    {
        const string& n1 = mit->first;
        for(XIT iit = m2.begin(); iit != m2.end(); ++iit)
        {
            const string& n2 = iit->first;
            float s = sim(sim_table, n1, n2);
#ifdef __DEBUG__
            std::cout << "sim score for neighbors node:" << n1 << ", and " << n2 << ", is:" << s << std::endl;
#endif
            sim_rank_score += s;
        }
    }
    float factor = C/(N_X * N_Y);
#ifdef __DEBUG__
    std::cout << "Factor:" << factor << std::endl;
#endif
    sim_rank_score *= factor;

    return sim_rank_score;
}

bool sort_fun(const string& a, const string& b)
{
    return !(a.compare(b));
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage:" << argv[0] << ", file" << std::endl;
        return -1;
    }
    vector<Record<string, string, int> > vec;
    char sep(',');
    bool ret = util::load_file_to_vector(argv[1], vec, sep);
    if (!ret)
    {
        return -1;
    }
    print_vec(vec);

    map<string, map<string, int> > list;
    vector<string> left_vec;
    vector<string> right_vec;    
    build_adjacency_table(vec, list, left_vec, right_vec);

    std::sort(left_vec.begin(), left_vec.end(), sort_fun);
    std::sort(right_vec.begin(), right_vec.end(), sort_fun);

    map<string, map<string, float> > sim_map;

    // init the sim
    size_t s1 = left_vec.size();
    size_t s2 = right_vec.size();
    for(size_t i=0; i<s1; ++i)
    {
        const string& n1 = left_vec[i];
        for(size_t j=0; j<s2; ++j)
        {
            const string& n2 = right_vec[j];
            sim_map[n1][n2] = 0;
            sim_map[n2][n1] = 0;
        }
    }
#ifdef __DEBUG__
    print_sim_map(sim_map);
#endif


#ifdef __DEBUG__
    map<string, map<string, int> >::iterator it = list.begin();
    for(; it != list.end(); ++it)
    {
        map<string, int>& m = it->second;
        map<string, int>::iterator iit = m.begin();
        std::cout << it->first << "->";
        for(; iit != m.end(); ++iit)
        {
            std::cout << "(" << iit->first << "," << iit->second << ")\t";
        }
        std::cout << endl;
    }
    size_t s1_ = left_vec.size();
    size_t s2_ = right_vec.size();

    std::cout << "Left nodes:" << std::endl;
    for(size_t i=0; i<s1_; ++i)
    {
        std::cout << left_vec[i] << "\t";
    }
    std::cout << endl;

    std::cout << "Right nodes:" << std::endl;
    for(size_t i=0; i<s2_; ++i)
    {
        std::cout << right_vec[i] << "\t";
    }
    std::cout << endl;
    std::cout << endl;
#endif

    map<string, map<string, float> > tmp_sim_map;

    int iter_num = 20;
    for(int x=0; x<iter_num; ++x)
    {
        std::cout << "+++++++++Run for:" << x << "++++++++++" << std::endl;
        // compute the left vector
        for(size_t i=0; i<left_vec.size(); ++i)
        {
            const string& N1 = left_vec[i];
            for(size_t j=i+1; j<left_vec.size(); ++j)
            {
                if (i == j)
                {
                    continue;
                }
                const string& N2 = left_vec[j];
#ifdef __DEBUG__
                std::cout << "compute sim for node pair(" << N1 << "," << N2 << ")" << std::endl;
#endif
                float sim = run_sim_rank(list, N1, N2, sim_map);
#ifdef __DEBUG__
                std::cout << "Get sim for node pair(" << N1 << "," << N2 << ") is " << sim << std::endl;
#endif
                // update the sim
                tmp_sim_map[N1][N2] = sim;
                tmp_sim_map[N2][N1] = sim;

            }

        }

        // compute the right vector
        for(size_t i=0; i<right_vec.size(); ++i)
        {
            const string& N1 = right_vec[i];
            for(size_t j=i+1; j<right_vec.size(); ++j)
            {
                const string& N2 = right_vec[j];
#ifdef __DEBUG__
                std::cout << "compute sim for node pair(" << N1 << "," << N2 << ")" << std::endl;
#endif
                float sim = run_sim_rank(list, N1, N2, sim_map);
#ifdef __DEBUG__
                std::cout << "Get sim for node pair(" << N1 << "," << N2 << ") is " << sim << std::endl;
#endif
                // update the sim
                tmp_sim_map[N1][N2] = sim;
                tmp_sim_map[N2][N1] = sim;

            }
        }

        sim_map.swap(tmp_sim_map);
        print_sim_map(sim_map);
    }

    return 0;
}
