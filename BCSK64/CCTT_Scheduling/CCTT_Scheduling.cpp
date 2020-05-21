/*==========================================================================================*\
**                        _           _ _   _     _  _         _                            **
**                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
**                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
**                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
**                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
\*==========================================================================================*/
//=====================================
//Solution Briefing - Foreword
/*
    
    [VI]: - Chương trình xếp lịch cho sự kiện Chào cờ truyền thống Khóa 64, ĐH Bách khoa Hà Nội
          - Thuật toán: Cặp ghép cực đại trên đồ thị hai phía + Xử lý CSV
          - Tác giả: bu1th4nh (Bùi Tiến Thành), K64-CTTN Toán tin

    (c) 2020 bu1th4nh. All rights reserved.

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
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt> 
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>

#include "utility.h"
#include "datatype.h"
#include "hopcroftkarp.h"
#pragma once


using namespace std;

//#define DEBUG
//#define PRINT_OUTPUT                  //uncomment this to print the matched output to stdout
#define OPTIONAL_FEATURE

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
#define FOR(i, x, y) for(int i=x; i<=(int)y; ++i)
#define FORl(i, x, y) for(int i=x; i<(int)y; ++i)
#define FORb(i, x, y) for(int i=x; i>=(int)y; --i)
#define FORlb(i, x, y) for(int i=x; i>(int)y; --i)


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
typedef vector<wstring> vwstr;



//=====================================
//Data decalration
HopcroftKarpMatching MatchingPool;

Class_InputData_Type_Pool           A;
Class_InputData_Type_Encode         Class_Encode;
Class_InputData_Type_Decode         Class_Decode;


Slots_InputData_Type_Pool           B, B2;
Slots_InputData_Type_Encode         Slots_Encode;
Slots_InputData_Type_Decode         Slots_Decode;

int nClass, nSlots, nClass_2;
vwstr Previous_Stage1;

wifstream CLASS1, CLASS2, SLOTS;
wofstream RESULT, DEBUG;



//=====================================
//Functions and procedures

//----------------------------------------------------------
//IO Declaration
void IODeclaration()
{
    _setmode(_fileno(stdout), _O_WTEXT); //needed for output
    _setmode(_fileno(stdin), _O_WTEXT); //needed for input

    CLASS1 = wifstream("class_stage1.csv");  CLASS1.imbue(loc);
    CLASS2 = wifstream("class_stage2.csv");  CLASS2.imbue(loc);
    SLOTS  = wifstream("slots.csv");         SLOTS.imbue(loc);

    RESULT = wofstream("final.csv");         RESULT.imbue(loc);
    DEBUG  = wofstream("debug.txt");         DEBUG.imbue(loc);

    RESULT << L"Tuần,Thứ,Kíp,STT Lớp,Thời gian,Sĩ số,Lớp,Viện\n";
}


//----------------------------------------------------------
//Enter (both stages)
void Stage1EnterData()
{
    wstring str;
    nClass = nSlots = 0;

    while (getline(CLASS1, str)) EnterClass(str, A, Class_Encode, Class_Decode);
    nClass_2 = nClass = A.size();

    while (getline(SLOTS, str)) EnterSlots(str, B, Slots_Encode, Slots_Decode);
    nSlots = B.size();

    //shuffle(whole(A), rng);
}      
void Stage2EnterData()
{
    wstring str;
    nClass = nSlots = 0;

    while (getline(CLASS2, str)) EnterClass(str, A, Class_Encode, Class_Decode);
    nClass = A.size();

    B = B2;
    for (auto sl : B) Slots_Encode[sl] = ++nSlots, Slots_Decode[nSlots] = sl;

    //shuffle(whole(A), rng);
}


//----------------------------------------------------------
//Build Graph
void BuildGraph()
{
    MatchingPool.reset(nClass, nSlots);


    for (auto cl : A)
    {
        for (auto sl : B)
        {
            bool cond = 0;
            if(cl.available[sl.date][sl.shift_id]) MatchingPool.addEdge(Class_Encode[cl], Slots_Encode[sl]);

            //wcerr << cond << sp << Class_Encode[cl] << sp << Slots_Encode[sl] << el;
        }
    }
}


//----------------------------------------------------------
//Process
wstring OutputMatch(int i, vi &partial_result)
{
    wstringstream matched; matched.imbue(loc);
    Slots_InputData_Type sl = Slots_Decode[i];
    Class_InputData_Type cl = Class_Decode[partial_result[i]];

    matched << sl.week << com << sl.date << com << sl.shift_id
        << com << sl.match_id << com << sl.information << com
        << cl.qty << com << cl.name << com << cl.school << el;

    return matched.str();
}
void Stage1Matching()
{
    MatchingPool.initMatch();

    int cnt = 0;
    vi partial_result = MatchingPool.extract_match_from_y();
    vi mat_check      = MatchingPool.extract_match_from_x();
    FORl(i, 1, partial_result.size())
    {
        if (partial_result[i])
        {
            Previous_Stage1.push_back(OutputMatch(i, partial_result));
            ++cnt;

            #ifdef PRINT_OUTPUT
            wcout << Previous_Stage1.back();
            #endif
        }
        else
        {
            //Assume there are no class unmatched in stage 1
            B2.push_back(Slots_Decode[i]);
            
            #ifdef PRINT_OUTPUT
            wcout << B2.back().week << sp << B2.back().date << sp << Slots_Decode[i].information << el;
            #endif
        }
    }

    FORl(i, 0, nClass) if (mat_check[i + 1] == 0) wcout << L"Found unmatched at: " << A[i].name << el;
    wcout << L"Stage 1 matched " << cnt << " out of " << nClass << " !" << el;
}
void Stage1Cleanup()
{
    A.clear(); B.clear();
    Class_Decode.clear();
    Class_Encode.clear();
    Slots_Decode.clear();
    Slots_Encode.clear();
}
void Stage2Matching()
{
    MatchingPool.initMatch();

    int cnt = 0;
    vi res = MatchingPool.extract_match_from_y();
    vi mat = MatchingPool.extract_match_from_x();

    for (auto x : Previous_Stage1) RESULT << x;
    FORl(i, 1, res.size()) 
    {
        wstring matched = OutputMatch(i, res);
        RESULT << matched;
        if(res[i]) ++cnt;

        #ifdef PRINT_OUTPUT
        wcout << matched;
        #endif
    }


    FORl(i, 0, nClass) if (mat[i + 1] == 0) wcout << L"Found unmatched at: " << A[i].name << el;
    wcout << L"Stage 2 matched " << cnt+Previous_Stage1.size() << " out of " << nClass+nClass_2 << " !" << el;
}


//----------------------------------------------------------
//Stage wraps
void Stage1()
{
    timeStart = chrono::steady_clock::now();

    Stage1EnterData();
    BuildGraph();
    Stage1Matching();
    Stage1Cleanup();

    timeEnd = chrono::steady_clock::now();
    wcout << L"Stage 1 completed with elapsed time: " << chrono::duration<double>(timeEnd - timeStart).count() << L" second(s)" << el;
}
void Stage2()
{
    timeStart = chrono::steady_clock::now();

    Stage2EnterData();
    BuildGraph();
    Stage2Matching();

    timeEnd = chrono::steady_clock::now();
    wcout << L"Stage 2 completed with elapsed time: " << chrono::duration<double>(timeEnd - timeStart).count() << L" second(s)" << el;
}


//----------------------------------------------------------
//Main Procedure
int wmain()
{
    Full_timeStart = chrono::steady_clock::now();

    IODeclaration();
    Stage1();
    Stage2();

    Full_timeEnd   = chrono::steady_clock::now();
    wcout << L"Program completed with elapsed time: " << chrono::duration<double>(Full_timeEnd - Full_timeStart).count() << L" second(s)" << el;
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//