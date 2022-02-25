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
#include <climits>
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
//OOP Version
class HopcroftKarpMatching
{
    #define FOR(i, x, y) for(int i=x; i<=y; ++i)
    const static int inf = INT_MAX;

    int m, n, nMatch;
    vector<int> d, MatchX, MatchY;
    vector<pair<int, int>> match_result;
    vector<vector<int>> adj;


    bool BFS()
    {
        /** \brief Phân hoạch đồ thị và tìm các đường tăng trưởng không giao nhau có ít cạnh nhất.
         *  \return TRUE nếu tồn tại đường tăng trưởng, FALSE nếu ngược lại
         */

        queue<int> q;
        int u;

        while(!q.empty()) q.pop();
        FOR(i, 1, m)
        {
            if(MatchX[i] == 0)
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
            if(d[u] < d[0]) for(int v: adj[u]) if(d[MatchY[v]] >= inf)
            {
                d[MatchY[v]] = d[u] + 1;
                q.push(MatchY[v]);
            }
        }

        return (d[0] < inf);
    }
    bool DFS(const int &u)
    {
        /** \brief Thủ tục DFS tìm đường tăng trưởng tại đỉnh u
         *  \param Đỉnh u
         *  \return TRUE nếu tìm được đường tăng trưởng, FALSE nếu ngược lại
         */


        for(int v: adj[u]) if(d[MatchY[v]] == d[u] + 1)
        {
            if(MatchY[v] == 0 || DFS(MatchY[v]))
            {
                MatchX[u] = v;
                MatchY[v] = u;
                return true;
            }
        }

        d[u] = inf;
        return false;
    }

public:

    void addEdge(int u, int v)
    {
        /** \brief Thêm cạnh vào đồ thị
        *   \param u, v: Hai đỉnh của đồ thị
        */

        adj[u].push_back(v);
    }
    void initMatch()
    {
        /** \brief Tiến hành thuật toán
         */
        nMatch = 0;
        while(BFS())
        {
            FOR(i, 1, m) if(MatchX[i] == 0)
            {
                if(DFS(i)) ++nMatch;

                //cerr << nMatch << "\n";
            }
        }

        FOR(i, 1, n)
        {
            if(int j = MatchY[i]) match_result.emplace_back(j, i);
        }
    }
    vector<pair<int, int>> extract_match_result()
    {
        /** \brief Trích xuất bộ ghép
         *  \return Một mảng pair<int, int> lưu bộ ghép
         */
        return match_result;
    }
    int extract_match_qty()
    {
        /** \brief Trích xuất kích cỡ bộ ghép
         *  \return Một số nguyên chr kích thước bộ ghép
        */
        return nMatch;
    }
    vector<int> extract_match_from_x()
    {
        /** \brief Extarct the result (left-side ====> right-side)
        */
        return MatchX;
    }
    vector<int> extract_match_from_y()
    {
        /** \brief Extarct the result (right-side ====> left-side)
        */
        return MatchY;
    }



    HopcroftKarpMatching(int __nLeft, int __nRight)
    {
        m = __nLeft, n = __nRight;
        MatchX = d = vector<int>(m+1, 0);
        MatchY = vector<int>(n+1, 0);
        adj = vector<vector<int>>(m+1);
    }
    HopcroftKarpMatching() {}
};



//=====================================End of algorithm=====================================================
//Enter
int m, n;
HopcroftKarpMatching match;

void Enter()
{
    int u, v, p;
	scanf("%d%d%d", &m, &n, &p);
	match = HopcroftKarpMatching(m, n);

	FOR(i, 1, p) {scanf("%d%d", &u, &v); match.addEdge(u, v);}
}

//Process
void Solve()
{
    match.initMatch();

    cout << match.extract_match_qty() << "\n";
}

//Main Procedure
int main()
{
    Enter();
    Solve();
    return 0;
}
