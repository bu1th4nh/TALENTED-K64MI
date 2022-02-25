///                       Test Generator v1.1 by bu1th4nh                        ///
/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <utility>

#if __cplusplus >= 201103L
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#endif // __cplusplus

using namespace std;

#include "test_lib.h"
#include "traditional.h"
#include "hopcroftkarp.h"

//=====================================
//Macroes
#define cma ','
#define sp ' '
#define el '\n'
#define task ""
#define maxinp ()
#define fi first
#define se second
#define pb push_back
#define whole(x) x.begin(),x.end()
#define whole_1(x) x.begin()+1,x.end()
#define r_whole(x) x.rbegin(),x.rend()
#define FOR(i, x, y) for(auto i=x; i<=y; ++i)
#define FORl(i, x, y) for(auto i=x; i<y; ++i)
#define FORb(i, x, y) for(auto i=x; i>=y; --i)
#define FORlb(i, x, y) for(auto i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))
#define what_is(x) cerr << #x << " is " << x << endl;
#define FILEOP()                        \
{                                       \
    freopen(task".inp", "r", stdin);    \
    freopen(task".out", "w", stdout);   \
}
#define FILEOP_DEBUG()                  \
{                                       \
    freopen(task".inp", "r", stdin);    \
    freopen(task".out", "w", stdout);   \
    freopen(task".err", "w", stderr);   \
}


#define TIME_SPAN fixed<<setprecision(15)<<chrono::duration_cast<chrono::duration<long double>>(timeEnd-timeStart).count()

//=====================================
//Typedefs
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vb> vvb;
typedef vector<vii> vvii;
int score = 0;
long long DFS, OTL;

auto timeStart = chrono::high_resolution_clock::now();
auto timeEnd   = chrono::high_resolution_clock::now();


//==================================================
//Checker
void Checker()
{
    int T = 100;
    vector<int> testcases({10, 50, 100, 200, 500, 1000, 5000});
    string info = "LVertexSize,RVertexSize,EdgeSize,TimeTraditionalAP,nDFSTraditionalAP,nOuterLoopTraditionalAP,TimeHopcroft-Karp,nDFSHopcroft-Karp,nOuterLoopHopcroft-Karp,SameResult,";

    ofstream logg("masterlogs.csv");
    logg << info << el;

    for(int n: testcases)
    {
        score = 0;
        stringstream gg; gg << "log_" <<  n << ".csv";
        cout << "N = " << n << el;
        ofstream log02(gg.str());
        log02 << info << el;


        FOR(iTest, 1, T)
        {
            cout << "Test #" << iTest << ":\n";
            stringstream ss;



            TraditionalMatching traditionalMatching(n, n);
            HopcroftKarpMatching hopcroftKarpMatching(n, n);




            timeStart = chrono::high_resolution_clock::now();
            int p = 0;
            if(n < 5000) p = rand_int(1, n*n-1);
            else p = rand_int(1, 10000000);
            set<pair<int, int>> edgeList;
            while(edgeList.size() < p)
            {
                edgeList.emplace(rand_int(1, n), rand_int(1, n));
            }
            for(ii edge: edgeList)
            {
                traditionalMatching.addEdge(edge.first, edge.second);
                hopcroftKarpMatching.addEdge(edge.first, edge.second);
            }
            timeEnd   = chrono::high_resolution_clock::now();
            ss << n << cma << n << cma << p << cma;
            cout << "Input generating completed with elapsed time: " << TIME_SPAN << " second(s)" << el;








            timeStart = chrono::high_resolution_clock::now();
            traditionalMatching.initMatch();
            timeEnd   = chrono::high_resolution_clock::now();

            ss << TIME_SPAN << cma;
            DFS = traditionalMatching.extract_DFS_steps();
            OTL = traditionalMatching.extract_outer_loops_steps();
            ss << DFS << cma << OTL << cma;

            cout << "Traditional AP Matching completed with elapsed time: " << TIME_SPAN << " second(s) with " << DFS << " DFS iteration(s) and " << OTL << " outer-loop iteration(s)" << el;





            timeStart = chrono::high_resolution_clock::now();
            hopcroftKarpMatching.initMatch();
            timeEnd   = chrono::high_resolution_clock::now();
            ss << TIME_SPAN << cma;
            DFS = hopcroftKarpMatching.extract_DFS_steps();
            OTL = hopcroftKarpMatching.extract_outer_loops_steps();
            ss << DFS << cma << OTL << cma;


            cout << "Hopcroft-Karp Matching completed with elapsed time: " << TIME_SPAN << " second(s) with " << DFS << " DFS iteration(s) and " << OTL << " outer-loop iteration(s)" << el;





            int ec = (traditionalMatching.extract_match_qty() == hopcroftKarpMatching.extract_match_qty());
            ss << (ec ? "TRUE" : "FALSE") << cma << el;
            puts((ec == 1) ? "Correct" : "Incorrect");
            score += ec;


            logg << ss.str();
            log02 << ss.str();
        }

        printf("Tester finished with partial score: %d / %d\n", score, T);
        printf("Nr. of Accepted tests:              %d / %d\n", score, T);
        printf("Nr. of WA tests:                    %d / %d\n", T-score, T);
    }


}


//Main Procedure
int main()
{
    Checker();
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
