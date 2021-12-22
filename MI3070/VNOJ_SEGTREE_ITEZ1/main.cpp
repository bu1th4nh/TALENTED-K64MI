/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
//Solution Briefing - Foreword



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

//#define DEBUG
//#define OPTIONAL_FEATURE

//=====================================
//Macroes
#define sp ' '
#define el '\n'
#define task "ITEZ1"
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

//Macroes - Optional
#ifdef OPTIONAL_FEATURE
    #define pc(x) putchar(x)
    #define gc() getchar()
#endif



//=====================================
//Auxilary Functions and Fast I/O
#ifdef OPTIONAL_FEATURE
    template<class T, class R> T max(const T &__X, const R &__Y)
    {
        return __X > __Y ? __X : __Y;
    }
    template<class T, class R> T min(const T &__X, const R &__Y)
    {
        return __X < __Y ? __X : __Y;
    }
    template<class T, class R> void maximize(T &__X, R __Y)
    {
        __X = __X > __Y ? __X : __Y;
    }
    template<class T, class R> void minimize(T &__X, R __Y)
    {
        __X = __X < __Y ? __X : __Y;
    }
    template<class T> int getBit(T &__X, int __i)
    {
        return ((__X >> __i) & 1) == 1;
    }
    template<class T> bool inRange(T __L, T __R, T __X)
    {
        return __L <= __X && __X <= __R;
    }
    template<class T> T __abs(T __X)
    {
        return (__X < 0) ? -__X : __X;
    }
#endif
//Fast I/O
template<class T> inline void read(T &__ret)
{
    __ret = T();
    char c = 0;
    bool neg = 0;

    while(isdigit(c) == 0 && c != '-') c = getchar();
    if(c == '-')
    {
        neg = 1;
        c = getchar();
    }

    for(; isdigit(c) != 0; c = getchar()) __ret = __ret * 10 + c - '0';
    __ret = (neg) ? -__ret : __ret;
}
template<class T> void print(T __X)
{
    if(__X < 0)
    {
        putchar('-');
        __X *= -1;
    }

    if(__X > 9) print(__X / 10);
    putchar(__X % 10 + '0');
}

//=====================================
//Classes
template<class T> struct SegmentTree
{
    #define lc id*2
    #define rc id*2+1
    typedef vector<T> vt;


    vt ST;
    int n;


    //Build
    void build(int id, int l, int r, const vt &a)
    {
        if(l > r) return;

        if(l == r) ST[id] = (a[l]);
        else
        {
            int mid = (l + r) / 2;
            build(lc, l, mid, a);
            build(lc + 1, mid+1, r, a);
            ST[id] = max(ST[lc], ST[rc]);
        }

    }
    //Update and queries
    void update(int id, int l, int r, int pos, T val)
    {
        if(pos < l || pos > r) return;
        if(l == r && l == pos)
        {
            ST[id] = val;
            return;
        }
        ST[id] = max(ST[id], val);

        int mid = (l + r) / 2;
        update(lc, l    , mid, pos, val);
        update(rc, mid+1, r  , pos, val);
        ST[id] = max(ST[lc], ST[rc]);
    }
    T query(int id, int l, int r, int ql, int qr)
    {
        if(ql > r || qr < l || l > r || ql > qr) return -INFINITY;
        if(ql <= l && r <= qr) return ST[id];

        int mid = (l + r) / 2;

        return max(query(lc, l, mid, ql, qr), query(rc, mid+1, r, ql, qr));
    }


    //Constructors and destructor
    SegmentTree(int __n)
    {
        ST = vt(4*__n+8, T());
    }
    SegmentTree() {}
};


//=====================================
//Typedefs
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<bool> vb;
typedef vector<int> vi;
int n, q;
vi a;

//Main Procedure
int main()
{
    FILEOP();
    cin >> n;
    a = vi(n+1, 0);
    FOR(i, 1, n) cin >> a[i];

    SegmentTree<int> ST(n);
    ST.build(1, 1, n, a);
    cin >> q;

    while(q--)
    {
        int type, u, v;
        cin >> type >> u >> v;

        if(type == 1)
        {
            ST.update(1, 1, n, u, v);
        }
        else
        {
            cout << ST.query(1, 1, n, u, v) << endl;
        }
    }

    return 0;
}
