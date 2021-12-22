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

//=====================================
//Macroes
#define sp ' '
#define el '\n'
#define task "ITLAZY"
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
string sizeinp = "";

auto timeStart = chrono::steady_clock::now();
auto timeEnd   = chrono::steady_clock::now();


//==================================================
//Input and answer generating procedures
void Generate_input(int n, int q)
{
    ofstream test_inp(task".inp");



    test_inp << n << el;
    FOR(i, 1, n)
    {
        test_inp << rand_int(0, 1000000000, 1) << sp;
    }
    test_inp << el;

    test_inp << q << el;
    FOR(i, 1, q)
    {
        int t = rand_int(1, 2);
        int L = rand_int(1, n);
        int R = rand_int(1, n);
        test_inp << t << sp;
        test_inp << min(L, R) << sp << max(L, R) << sp;

        if(t == 1)
        {
            test_inp << rand_int(0, 1000000000, 1);
        }
        test_inp << el;
    }


    //Write your input-generating code here
}
void Generate_answer()
{
    ifstream test_inp(task".inp");
    ofstream test_ans(task".ans");

    //Write your answer-generating code here
}

//==================================================
//Checker
void Checker(int sz)
{
    int T = 40;

    ofstream logg("logs_" + to_string(sz) + ".csv");
    logg << "Time O(n^2),Time O(nlogn)," << el;

    FOR(iTest, 1, T)
    {
        cout << "Test #" << iTest << ":\n";


        Generate_input(sz, sz);
        cout << "Input generating completed\n";



        timeStart = chrono::steady_clock::now();
        system("VNOJ_SEGTREE_ITLAZY_ON2.exe");
        timeEnd   = chrono::steady_clock::now();
        logg << chrono::duration<double>(timeEnd - timeStart).count() << ",";
        cout << "O(n^2) completed with elapsed time: " << chrono::duration<double>(timeEnd - timeStart).count() << " second(s)" << el;


        timeStart = chrono::steady_clock::now();
        system("VNOJ_SEGTREE_ITLAZY.exe");
        timeEnd   = chrono::steady_clock::now();
        logg << chrono::duration<double>(timeEnd - timeStart).count() << "," << el;
        cout << "O(nlogn) completed with elapsed time: " << chrono::duration<double>(timeEnd - timeStart).count() << " second(s)" << el;


    }


}


//Main Procedure
int main()
{
    cout << "Press any key to begin test\n";
    system("pause");


    vi N({1000, 5000, 10000, 50000, 100000});
    for(int gg: N)
    {
        cout << "N = " << gg << el;
        Checker(gg);
    }
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//