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
#include<math.h>
#include<stdbool.h>
#include "Matrix.h"


//#define DEBUG
#define OPTIONAL_FEATURE
#define FRIENDLY_UX

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
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)
#define MEMS(x, val) memset(x, val, sizeof(x))


//Macroes - Optional
#ifdef OPTIONAL_FEATURE
    #define pc(x) putchar(x)
    #define gc() getchar()
#endif

#pragma once
//=====================================
//Typedefs
typedef unsigned long long ull;
struct Matrix A, B;
int m, n;


//=====================================
//Functions and procedures
void Enter()
{
    #ifdef FRIENDLY_UX
    printf("Nhap kich co ma tran: (so dong, so cot) = ");
    #endif // FRIENDLY_UX

    scanf("%d%d", &n, &m);
    A = B = mat_zeros(n, m);

    #ifdef FRIENDLY_UX
    printf("Nhap cac phan tu ma tran A: \n");
    #endif // FRIENDLY_UX

    A = mat_scan(n, m);

    #ifdef FRIENDLY_UX
    printf("Nhap cac phan tu ma tran B: \n");
    #endif // FRIENDLY_UX

    B = mat_scan(n, m);
}

//Process
void Solve()
{
    MAT_TYPE sum_edge = 0;
    FORl(i, 0, m)   sum_edge += A.mat[0][i] + A.mat[n-1][i];
    FORl(i, 1, n-1) sum_edge += A.mat[i][0] + A.mat[i][m-1];

    #ifdef FRIENDLY_UX
    printf("Tong phan tu tren 4 canh bien ma tran A: ");
    #endif // FRIENDLY_UX
    printf(MAT_TYPE_IO_ARG, sum_edge); putchar('\n');

    if(mat_is_square(A))
    {
        #ifdef FRIENDLY_UX
        printf("Ma tran nay vuong. Tong phan tu 2 duong cheo ma tran A: ");
        #endif // FRIENDLY_UX

        MAT_TYPE complement_value = (n & 1) ? A.mat[(n >> 1)][(n >> 1)] : 0;
        printf(MAT_TYPE_IO_ARG, mat_trace(A) + mat_rev_trace(A) - complement_value); putchar('\n');
    }

    #ifdef FRIENDLY_UX
    printf("A + B = \n");
    #endif // FRIENDLY_UX
    mat_print(mat_add(A, B));


    #ifdef FRIENDLY_UX
    printf("A - B = \n");
    #endif // FRIENDLY_UX
    mat_print(mat_sub(A, B));


    #ifdef FRIENDLY_UX
    printf("A * B = \n");
    #endif // FRIENDLY_UX
    mat_print(mat_mul(A, B));
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
