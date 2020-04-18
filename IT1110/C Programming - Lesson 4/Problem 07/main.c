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
#include<math.h>

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
ld a, b, c, p, s;

//=====================================
//Functions and procedures
//Enter
void Enter()
{
    #ifdef FRIENDLY_UX
    printf("Hay nhap 3 so a, b, c: ");
    #endif // FRIENDLY_UX

    scanf("%lf%lf%lf", &a, &b, &c);
}

//Process
void Solve()
{
    bool cond1 = a - b < c && c < a + b;
    bool cond2 = b - c < a && a < b + c;
    bool cond3 = c - a < b && b < c + a;

    if(cond1 && cond2 && cond3)
    {
        p = (a + b + c) / 2.00;
        s = sqrt(p*(p-a)*(p-b)*(p-c));

        #ifdef FRIENDLY_UX
        printf("Bo so (a, b, c) = (%lf, %lf, %lf) la do dai ba canh cua 1 tam giac\n", a, b, c);
        printf("Dien tich tam giac: %lf\n", s);
        #else
        print("%lf\n", s);
        #endif // FRIENDLY_UX
    }
    else
    {
        #ifdef FRIENDLY_UX
        printf("Bo so (a, b, c) = (%lf, %lf, %lf) khong la do dai ba canh cua 1 tam giac\n", a, b, c);
        #else
        printf("-1");
        #endif // FRIENDLY_UX
    }
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
