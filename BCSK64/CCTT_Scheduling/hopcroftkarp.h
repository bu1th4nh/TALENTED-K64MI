/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
//Briefing
/*
    This is the implementation for finding Maximum Matching in unweighted Biparttite Graph
    using Hopcroft - Karp Algorithm
    * Status: tested
    * Author: bu1th4nh
*/
//=====================================
//Libraries and namespaces
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
using namespace std;


//=====================================
//Macros
#define sp L' '
#define el L'\n'
#define com L','
#define fi first
#define se second
#define pb push_back
#define maxinp (int)()
#define siz(x) (int)(x.size())
#define len(x) (int)(x.length())
#define whole(x) x.begin(), x.end()
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)

const int inf = 1234567890;
//=====================================
//Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vb> vvb;
typedef vector<vii> vvii;

//=====================================
//OOP Version
class HopcroftKarpMatching
{

public:

    const int inf = 1234567890;

    typedef queue<int> qi;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vii> vvii;

    int m, n, nMatch;
    vi d, matx, maty;
    vvi adj;

private:

    bool BFS()
    {
        /** \brief Find the length of shortest augmenting path from source vertex and partition the graph into layers
         * \return Return true if found an aug. path, false otherwise
         */

        qi q;
        int u;

        while(!q.empty()) q.pop();
        FOR(i, 1, m)
        {
            if(matx[i] == 0)
            {
                d[i] = 0;
                q.push(i);
            }
            else d[i] = inf;
        }

        d[0] = inf;
        while(!q.empty())
        {
            u = q.front(); q.pop();
            if(d[u] < d[0]) for(int v: adj[u]) if(d[maty[v]] >= inf)
            {
                d[maty[v]] = d[u] + 1;
                q.push(maty[v]);
            }
        }

        return (d[0] < inf);
    }
    bool DFS(const int &u)
    {
        /** \brief Flip the edge status along the augmenting path
         */

        if(u == 0) return true;
        for(int v: adj[u]) if(d[maty[v]] == d[u] + 1)
        {
            if(DFS(maty[v]))
            {
                matx[u] = v;
                maty[v] = u;
                return true;
            }
        }
        d[u] = inf;
        return false;
    }

public:
    void addEdge(int u, int v)
    {
        /** \brief Add an edge to the bipartite graph
        *   \param u: ID of left-vertex
        *   \param v: ID of right-vertex
        */

        adj[u].pb(v);

        //cerr << "Edge " << u << " - " << v << " is added!\n";
    }
    void initMatch()
    {
        /** \brief Start the algorithm
         */
        nMatch = 0;
        while(BFS())
        {
            FOR(i, 1, m) if(matx[i] == 0)
            {
                if(DFS(i)) ++nMatch;

                //cerr << nMatch << "\n";
            }
        }
    }
    vi extract_match_from_x()
    {
        /** \brief Extarct the result (left-side ====> right-side)
        */
        return matx;
    }
    vi extract_match_from_y()
    {
        /** \brief Extarct the result (right-side ====> left-side)
        */
        return maty;
    }
    int extract_match_qty()
    {
        /** \brief Extarct the number of maximum match
        */
        return nMatch;
    }
    void reset(int __m, int __n)
    {
        m = __m, n = __n;
        matx = d = vi(m + 1, 0);
        maty = vi(n + 1, 0);
        adj = vvi(m + 1);
    }

    HopcroftKarpMatching(int __m, int __n)
    {
        m = __m, n = __n;
        matx = d = vi(m+1, 0);
        maty = vi(n+1, 0);
        adj = vvi(m+1);
    }
    HopcroftKarpMatching() {}

    ~HopcroftKarpMatching() {}

};
