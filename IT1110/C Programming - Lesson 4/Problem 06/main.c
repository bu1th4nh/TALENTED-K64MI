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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>
#include<stdbool.h>

//#define DEBUG
#define OPTIONAL_FEATURE

//=====================================
//Macroes
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


#define FRIENDLY_UX



//=====================================
//Auxilary Functions and Fast I/O
#ifdef __cplusplus
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
    template<class T> T __sqr(T __X)
    {
        return __X * __X;
    }


//Fast I/O
template<class T> inline void scan(T &__ret)
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
#endif
//=====================================
//Constants



//=====================================
//Typedefs
typedef double ld;
typedef long long ll;
typedef unsigned long long ull;
ld a, b, c, d, e;

//=====================================
//Functions and procedures
//Enter
void Enter()
{
    bool cond1, cond2, cond3, cond4, startProg;
    cond1 = cond2 = cond3 = cond4 = startProg = 1;

    while(cond1 || cond2 || cond3 || cond4)
    {
        #ifdef FRIENDLY_UX
        printf(startProg ? "Hay nhap vao cac so a, b, c, d, e: " : "Dau vao khong hop le, hay nhap lai: ");
        #endif // FRIENDLY_UX

        scanf("%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e);
        cond1 = (a == b) || (a == c) || (a == d) || (a == e);
        cond2 = (b == c) || (b == d) || (b == e);
        cond3 = (c == d) || (c == e);
        cond4 = (d == e);
        startProg = 0;
    }

}

//Process
void Solve()
{
    ld min, max, min2nd, max2nd;
    min = max = min2nd = max2nd = a;

    if(min > b) min = b; if(max < b) max = b;
    if(min > c) min = c; if(max < c) max = c;
    if(min > d) min = d; if(max < d) max = d;
    if(min > e) min = e; if(max < e) max = e;

    min2nd = 1.0/0.0;
    max2nd = -1.0/0.0;

    if(min2nd > a &&  a != min) min2nd = a;  if(max2nd < a &&  a != max) max2nd = a;
    if(min2nd > b &&  b != min) min2nd = b;  if(max2nd < b &&  b != max) max2nd = b;
    if(min2nd > c &&  c != min) min2nd = c;  if(max2nd < c &&  c != max) max2nd = c;
    if(min2nd > d &&  d != min) min2nd = d;  if(max2nd < d &&  d != max) max2nd = d;
    if(min2nd > e &&  e != min) min2nd = e;  if(max2nd < e &&  e != max) max2nd = e;

    #ifdef FRIENDLY_UX
    printf("So thuc gia tri lon nhat la: %lf\n", max);
    printf("So thuc gia tri lon thu 2 la: %lf\n", max2nd);
    printf("So thuc gia tri nho nhat la: %lf\n", min);
    printf("So thuc gia tri nho thu 2 la: %lf\n", min2nd);
    #else
    printf("%lf\n", max);
    printf("%lf\n", max2nd);
    printf("%lf\n", min);
    printf("%lf\n", min2nd);
    #endif // FRIENDLY_UX


}


//Main Procedure
int main(int argc, char *argv[])
{
    Enter();
    Solve();
	return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
