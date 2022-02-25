/*==============================================================================================================*\
**                                  _           _ _   _     _  _         _                                      **
**                                 | |__  _   _/ | |_| |__ | || |  _ __ | |__                                   **
**                                 | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                                  **
**                                 | |_) | |_| | | |_| | | |__   _| | | | | | |                                 **
**                                 |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                                 **
\*==============================================================================================================*/
//=====================================
//Briefing
/*
    This is the implementation for finding Maximum Matching in unweighted Biparttite Graph
    using traditional Augmenting Path Algorithm

    * Status: tested, with OOP
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
#include <vector>
#include <utility>
using namespace std;

//=====================================
//OOP Version
class TraditionalMatching
{
    #define FOR(i, x, y) for(int i=x; i<=y; ++i)

    vector<int> assigned;
    vector<int> visited;
    vector<pair<int, int>> match_result;
    vector<vector<int>> adj;
    int m, n, nMatch;


    bool FindAP(int u, int t)
    {
        /** \brief Thủ tục DFS tìm đường tăng trưởng tại đỉnh u và đỉnh khởi đầu là t
         *  \param Đỉnh u, đỉnh khởi đầu t chưa được phủ bởi M
         *  \return TRUE nếu tìm được đường tăng trưởng, FALSE nếu ngược lại
         */

        if(visited[u] != t) visited[u] = t;
        else return false;

        for(int v: adj[u])
        {
            if(!assigned[v] || FindAP(assigned[v], t))
            {
                assigned[v] = u;
                return true;
            }
        }

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

        FOR(i, 1, m)
        {
            nMatch += (int)FindAP(i, i);
        }

        FOR(i, 1, n)
        {
            if(int j = assigned[i]) match_result.emplace_back(j, i);
        }

    }
    vector<pair<int, int>> extract_match_result()
    {
        /** \brief Trích xuất bộ ghép
        */
        return match_result;
    }
    int extract_match_qty()
    {
        /** \brief Trích xuất kích cỡ bộ ghép
        */
        return nMatch;
    }


    TraditionalMatching(int __nLeft, int __nRight)
    {
        m = __nLeft, n = __nRight;
        assigned = vector<int>(n+1, 0);
        visited = vector<int>(m+1, 0);
        adj = vector<vector<int>>(m+1);
    }
    TraditionalMatching() {}
};





//=====================================End of algorithm=====================================================
//Enter
int m, n;
TraditionalMatching match;

void Enter()
{
    int u, v;
	scanf("%d%d", &m, &n);
	match = TraditionalMatching(m, n);

	while(scanf("%d%d", &u, &v) == 2) match.addEdge(u, v);
}

//Process
void Solve()
{
    match.initMatch();

    cout << match.extract_match_qty() << "\n";
    auto matches = match.extract_match_result();

    for(auto edges: matches)
    {
        printf("%d %d\n", edges.first, edges.second);
    }
}

//Main Procedure
int main()
{
    Enter();
    Solve();
    return 0;
}
