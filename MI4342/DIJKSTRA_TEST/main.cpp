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
#define task "DIJKSTRA"
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


auto timeStart = chrono::steady_clock::now();
auto timeEnd   = chrono::steady_clock::now();
int n, m, s, t;

//==================================================
//Input and answer generating procedures
void Generate_input()
{
    ofstream test_inp(task".inp");

    n = 1000;
    m = 30000;

    s = rand_int(0, n-1);
    t = rand_int(0, n-1);

    cout << "=========================================================\n";
    cout << "Input\n";
    cout << "n, m, s, t = " << n << sp << m << sp << s << sp << t << el;

    set<ii> gg;
    while(gg.size() < m)
    {
        int u = rand_int(0, n-1);
        int v = rand_int(0, n-1);
        while(u == v) v = rand_int(0, n-1);
        gg.emplace(min(u,v), max(u, v));
    }

    for(auto x: gg)
    {
        int c = rand_int(1, 20);
        test_inp << x.fi << el;
        test_inp << x.se << el;
        test_inp << c << el;

        //cout << x.fi << sp << x.se << sp << c << el;
    }

}
void Generate_answer()
{
    ifstream test_inp(task".inp");

    vvii adj;
    vi dist;
    vi trace;



    adj = vvii(n+1);
    trace = vi(n+1, 0);

    FOR(i, 1, m)
    {
        int u, v, c;
        test_inp >> u >> v >> c;
        adj[u].pb(ii(c, v));
        adj[v].pb(ii(c, u));
    }

    const int inf = 1000000007;
    int u, v, du, uv;
    priority_queue<ii, vii, greater<ii>> pq;

    int start = s;
    dist = vi(n+1, inf);
    dist[start] = 0;
    trace[s] = -1;
    pq.push(ii(0, start));

    while(!pq.empty())
    {
        u = pq.top().second;
        du = pq.top().first;
        pq.pop();

        if(du != dist[u]) continue;

        for(auto x: adj[u])
        {
            v = x.second;
            uv = x.first;

            if(dist[u] + uv < dist[v])
            {
                pq.push(ii((dist[v] = dist[u] + uv), v));
                trace[v] = u;
            }
        }
    }

    cout << "=========================================================\n";
    cout << "Answer\n";

    printf("Shortest distance from %d to %d is: %d\n", s, t, dist[t]);
    if(s == t)
    {
        printf("%d and %d is the same\n", s, t);
    }
    else
    {
        printf("Shortest path from %d to %d: ", s, t);
        while(s != t)
        {
            printf("%d <- ", t);
            t = trace[t];
        }
        printf("%d\n", s);

    }


    //Write your answer-generating code here
}

//==================================================
//Checker
void Checker()
{
    Generate_input();
    Generate_answer();
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
