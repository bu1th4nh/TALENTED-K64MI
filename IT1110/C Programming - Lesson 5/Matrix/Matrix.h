/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//****************************************************************
//
//      This file declares Matrix data type
//      and its utilities and operations
//
//      (c) 2020, bu1th4nh. Some rights reserved.
//
//****************************************************************
//Libraries and namespaces
//#include <bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>
#include<math.h>
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


//=================================================================================
//Matrix Setup & I/O Args
#define MAT_TYPE long long
#define MAT_TYPE_IO_ARG "%lld"

struct Matrix
{
    MAT_TYPE **mat;
    int n_col, n_row;
};

//*************************************************
//Matrix Construction
//*************************************************
struct Matrix mat_zeros(int n_col, int n_row)
{
    struct Matrix ret;
    ret.n_col = n_col;
    ret.n_row = n_row;

    //Memory allocation
    ret.mat = (MAT_TYPE **)malloc(n_row * sizeof(MAT_TYPE *));      //Good game well-play =)))))
    FORl(i, 0, n_row)
    {
        ret.mat[i] = (MAT_TYPE *)malloc(n_col * sizeof(MAT_TYPE));
    }

    FORl(i, 0, n_row) FORl(j, 0, n_col) ret.mat[i][j] = 0;
    return ret;
}
struct Matrix mat_identity(int sz)
{
    struct Matrix ret = mat_zeros(sz, sz);
    FORl(i, 0, sz) ret.mat[i][i] = 1;
    return ret;
};

//*************************************************
//Matrix Utilities
//*************************************************
//Check utils
bool mat_is_square(struct Matrix A)
{
    return A.n_col == A.n_row;
}
bool mat_is_symmetric(struct Matrix A)
{
    //Is A square?
    if(!mat_is_square(A)) return 0;


    FORl(i, 0, A.n_col) FORl(j, 0, i-1)
    {
        if(A.mat[i][j] != A.mat[j][i]) return 0;
    }
    return 1;
}

//Calculate utils
MAT_TYPE mat_trace(struct Matrix A)
{
    //Is A square?
    if(!mat_is_square(A)) return 0;

    //Is A square?
    MAT_TYPE ret = 0;
    int n = A.n_row;

    FORl(i, 0, n) ret += A.mat[i][i];
    return ret;
}
MAT_TYPE mat_rev_trace(struct Matrix A)
{
    if(!mat_is_square(A)) return 0;

    MAT_TYPE ret = 0;
    int n = A.n_row;

    FORl(i, 0, n) ret += A.mat[i][n-i-1];
    return ret;
}
MAT_TYPE * mat_extract_row(int u, struct Matrix A)
{
    //0-indexed
    assert(u < A.n_row);
    return A.mat[u];
}


//*************************************************
//Matrix Operation
//*************************************************
struct Matrix mat_scale(struct Matrix A, MAT_TYPE x)
{
    int row = A.n_row;
    int col = A.n_col;
    struct Matrix ret = mat_zeros(row, col);

    FORl(i, 0, row)
    {
        FORl(j, 0, col) ret.mat[i][j] = A.mat[i][j] * x;
    }
    return ret;
}
struct Matrix mat_add(struct Matrix A, struct Matrix B)
{
    assert(A.n_row == B.n_row && A.n_col == B.n_col);

    struct Matrix ret = mat_zeros(A.n_row, A.n_col);
    int row = A.n_row;
    int col = A.n_col;

    FORl(i, 0, row)
    {
        FORl(j, 0, col) ret.mat[i][j] = A.mat[i][j] + B.mat[i][j];
    }
    return ret;
}
struct Matrix  mat_sub(struct Matrix A, struct Matrix B)
{
    return mat_add(A, mat_scale(B, -1));
}
struct Matrix mat_mul(struct Matrix A, struct Matrix B)
{
    assert(A.n_col == B.n_row);

    struct Matrix ret = mat_zeros(A.n_row, B.n_col);
    FORl(i, 0, A.n_row)
    {
        FORl(j, 0, B.n_col)
        {
            FORl(k, 0, A.n_col)
            {
                ret.mat[i][j] += A.mat[i][k] * B.mat[k][j];
            }
        }
    }
    return ret;
};


//*************************************************
//Matrix In/Out
//*************************************************
struct Matrix mat_scan(int n_row, int n_col)
{
    struct Matrix ret = mat_zeros(n_row, n_col);
    FORl(i, 0, n_row)
    {
        FORl(j, 0, n_col)
        {
            scanf(MAT_TYPE_IO_ARG, &ret.mat[i][j]);
        }
    }
    return ret;
}
void mat_print(struct Matrix A)
{
    FORl(i, 0, A.n_row)
    {
        FORl(j, 0, A.n_col)
        {
            printf(MAT_TYPE_IO_ARG, A.mat[i][j]);
            putchar(' ');
        }
        putchar('\n');
    }
}


