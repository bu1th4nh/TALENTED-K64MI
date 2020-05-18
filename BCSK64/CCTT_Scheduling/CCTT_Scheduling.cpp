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
#include <chrono>
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
#include <random>
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

#include "hopcroftkarp.h"
#pragma once

#if __cplusplus >= 201103L
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#endif // __cplusplus

using namespace std;

//#define DEBUG
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
#define FOR(i, x, y) for(int i=x; i<=y; ++i)
#define FORl(i, x, y) for(int i=x; i<y; ++i)
#define FORb(i, x, y) for(int i=x; i>=y; --i)
#define FORlb(i, x, y) for(int i=x; i>y; --i)


//=====================================
//Constants
locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
vector<wstring> Morning({ L"sáng nghỉ", L"sáng", L"cả ngày", L"sáng+chiều", L"sáng và chiều", L"" });
vector<wstring> Afternoon({ L"chiều nghỉ", L"chiều", L"cả ngày", L"sáng+chiều", L"sáng và chiều", L"" });
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//=====================================
//Data defs
struct Class_InputData_Type
{
    wstring name, school, monday, wednesday, friday;
    int qty;

    Class_InputData_Type()
    {
        name = school = monday = wednesday = friday = L"";
        qty = 0;
    }
    Class_InputData_Type(wstring inputted)
    {
        int cnt = 0;
        wstring word[6];

        for (auto c : inputted)
        {
            if (c == L',') ++cnt;
            else word[cnt] += c;
        }

        
        FOR(i, 3, 5) for(auto &ch: word[i]) ch = towlower(ch);

        name        = word[0];
        school      = word[1];
        monday      = word[3];
        wednesday   = word[4]; 
        friday      = word[5];
        qty         = stoi(word[2]);
    }


    bool operator< (const Class_InputData_Type& oth) const
    {
        return make_tuple(qty, school, name) < make_tuple(oth.qty, oth.school, oth.name);
    }
};

struct Slots_InputData_Type
{
    wstring information;
    int date, week, shift_id, match_id, seed;

    Slots_InputData_Type()
    {
        date = week = shift_id = match_id = seed = 0;
        information = L"";
    }
    Slots_InputData_Type(int _week, int _date, int _shift_id, int _match_id, wstring _information)
    {
        srand(time(NULL));

        seed        = rand();
        week        = _week;
        date        = _date;
        shift_id    = _shift_id;
        match_id    = _match_id;
        information = _information;
    }
    Slots_InputData_Type(wstring inputted)
    {
        srand(time(NULL));
        seed = rand();
        int cnt = 0;
        wstring word[10];

        for (auto c : inputted)
        {
            if (c == L',') ++cnt;
            else word[cnt] += c;
        }

        week        = stoi(word[0]);
        date        = stoi(word[1]);
        shift_id    = stoi(word[2]);
        information = word[3];
    }


    bool operator< (const Slots_InputData_Type& oth) const
    {
        return make_tuple(seed, week, date, shift_id, match_id) < make_tuple(oth.seed, oth.week, oth.date, oth.shift_id, oth.match_id);
    }
    bool operator== (const Slots_InputData_Type& oth) const
    {
        return make_tuple(seed, week, date, shift_id, match_id) == make_tuple(oth.seed, oth.week, oth.date, oth.shift_id, oth.match_id);
    }

};

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


typedef vector<Class_InputData_Type>                               Class_InputData_Type_Pool;
typedef map<Class_InputData_Type, int>                             Class_InputData_Type_Encode;
typedef map<int, Class_InputData_Type>                             Class_InputData_Type_Decode;       //Vertex -> Data


typedef vector<Slots_InputData_Type>                               Slots_InputData_Type_Pool;
typedef map<Slots_InputData_Type, int>                             Slots_InputData_Type_Encode;
typedef map<int, Slots_InputData_Type>                             Slots_InputData_Type_Decode;       //Vertex -> Data




//=====================================
//Data decalration
HopcroftKarpMatching MatchingPool;

Class_InputData_Type_Pool           A;
Class_InputData_Type_Encode         Class_Encode;
Class_InputData_Type_Decode         Class_Decode;


Slots_InputData_Type_Pool           B;
Slots_InputData_Type_Encode         Slots_Encode;
Slots_InputData_Type_Decode         Slots_Decode;

int nClass, nSlots, nClass_2;
vwstr Previous_Stage1;

//=====================================
//Functions and procedures
//Enter (both stages)
void Stage1EnterData()
{
    wstring str;
    wifstream CLASS("class_stage1.csv");  CLASS.imbue(loc);
    wifstream SLOTS("slots.csv");  SLOTS.imbue(loc);
    nClass = nSlots = 0;

    while (getline(CLASS, str))
    {
        A.emplace_back(str); 
        Class_Encode[A.back()] = ++nClass;
        Class_Decode[nClass]   = A.back();
    }
    nClass_2 = nClass;

    while (getline(SLOTS, str))
    {
        Slots_InputData_Type s1(str); s1.match_id = 1;
        Slots_InputData_Type s2(str); s2.match_id = 2;

        B.push_back(s1); Slots_Encode[s1] = B.size(); Slots_Decode[B.size()] = s1;
        B.push_back(s2); Slots_Encode[s2] = B.size(); Slots_Decode[B.size()] = s2;
        
        
        if (s1.week >= 44) 
        {
            Slots_InputData_Type s3(str); 
            s3.match_id = 3;
            B.push_back(s3); 
            Slots_Encode[s3] = B.size(); 
            Slots_Decode[B.size()] = s3; 
        }
        
    }

    nSlots = B.size();

    shuffle(whole(A), rng);
}
void Stage2EnterData()
{
    wstring str;
    wifstream CLASS("class_stage2.csv");   CLASS.imbue(loc);
    wifstream SLOTS("result_stage1.csv");  SLOTS.imbue(loc);
    nClass = nSlots = 0;

    while (getline(CLASS, str))
    {
        A.emplace_back(str);
        Class_Encode[A.back()] = ++nClass;
        Class_Decode[nClass] = A.back();
    }


    while (getline(SLOTS, str))
    {
        wstring word[10];
        int cnt = 0;

        for (auto c : str)
        {
            if (c == L',') ++cnt;
            else word[cnt] += c;
        }

        if (stoi(word[5]) == 0)
        {
            Slots_InputData_Type sl = Slots_InputData_Type(
                stoi(word[0]),
                stoi(word[1]),
                stoi(word[2]),
                stoi(word[3]),
                word[4]
            );

            B.push_back(sl);
            Slots_Encode[sl] = B.size();
            Slots_Decode[B.size()] = sl;
        }
        else Previous_Stage1.push_back(str);
    }

    nSlots = B.size();
    //random_shuffle(whole(A));
}



//Build Graph
bool inPool(wstring val, vwstr& vect)
{
    sort(whole(vect));
    return binary_search(whole(vect), val);
}
void BuildGraph()
{
    MatchingPool.reset(nClass, nSlots);


    for (auto cl : A)
    {
        for (auto sl : B)
        {
            bool cond = 0;
            if (sl.date == 2 && sl.shift_id <= 3 && inPool(cl.monday, Morning))        cond = 1;
            if (sl.date == 2 && sl.shift_id >  3 && inPool(cl.monday, Afternoon))      cond = 1;
            
            if (sl.date == 4 && sl.shift_id <= 3 && inPool(cl.wednesday, Morning))     cond = 1;
            if (sl.date == 4 && sl.shift_id >  3 && inPool(cl.wednesday, Afternoon))   cond = 1;
            
            if (sl.date == 6 && sl.shift_id <= 3 && inPool(cl.friday, Morning))        cond = 1;
            if (sl.date == 6 && sl.shift_id >  3 && inPool(cl.friday, Afternoon))      cond = 1;


            if (cond) MatchingPool.addEdge(Class_Encode[cl], Slots_Encode[sl]);

            //wcerr << cond << sp << Class_Encode[cl] << sp << Slots_Encode[sl] << el;
        }
    }
}


//Process
void InitializeMatching()
{
    MatchingPool.initMatch();
}
void Stage1Cleanup()
{
    A.clear(); B.clear();
    Class_Decode.clear();
    Class_Encode.clear();
    Slots_Decode.clear();
    Slots_Encode.clear();
}



//Stage 1 Output Data
void Stage1OutputData()
{
    int cnt = 0;
    vi res = MatchingPool.extract_match_from_y();
    wofstream fo("result_stage1.csv"); fo.imbue(loc);

    FORl(i, 1, res.size())
    {
        Slots_InputData_Type sl = Slots_Decode[i];
        Class_InputData_Type cl = Class_Decode[res[i]];

        fo << sl.week << com << sl.date << com << sl.shift_id 
           << com << sl.match_id << com << sl.information << com 
           << cl.qty << com << cl.name << com << cl.school << el;
        cnt += (cl.qty != 0);

        wcout << sl.week << L"," << sl.date << com << sl.shift_id
            << com << sl.match_id << com << sl.information << com
            << cl.qty << com << cl.name << com << cl.school << el;
    }

    wcout << L"Stage 1 matched " << cnt << " out of " << nClass << " !" << el;
}
//Stage 2 Output Data
void Stage2OutputData()
{
    int cnt = 0;
    vi res = MatchingPool.extract_match_from_y();
    wofstream fo("final.csv"); fo.imbue(loc);

    fo << L"Tuần,Thứ,Kíp,STT Lớp,Thời gian,Sĩ số,Lớp,Viện\n";
    for (auto x : Previous_Stage1) fo << x << el;
    FORl(i, 1, res.size())
    {
        Slots_InputData_Type sl = Slots_Decode[i];
        Class_InputData_Type cl = Class_Decode[res[i]];

        fo << sl.week << L"," << sl.date << com << sl.shift_id
            << com << sl.match_id << com << sl.information << com
            << cl.qty << com << cl.name << com << cl.school << el;
        cnt += (cl.qty != 0);


        wcout << sl.week << L"," << sl.date << com << sl.shift_id
            << com << sl.match_id << com << sl.information << com
            << cl.qty << com << cl.name << com << cl.school << el;
    }


    wcout << L"Stage 2 matched " << cnt+Previous_Stage1.size() << " out of " << nClass+nClass_2 << " !" << el;
}


//Debugging
void Debug()
{
    wofstream DEBUG("debug.csv");  DEBUG.imbue(loc);

    for (auto x : A)
    {
        DEBUG << x.name << com << x.monday << com << x.wednesday << com << x.friday << el;
    }

    /*
    for (auto x : B)
    {
        DEBUG << x.week << sp << x.date << sp << x.shift_id << sp << x.match_id << sp << x.information << el;
    }

    DEBUG << el << el;
    for (auto x : Slots_Encode)
    {
        DEBUG << x.first.information << sp << x.first.match_id << sp << x.second << el;
    }
    */
}



//Main Procedure
int wmain()
{
    _setmode(_fileno(stdout), _O_WTEXT); //needed for output
    _setmode(_fileno(stdin), _O_WTEXT); //needed for input

    Stage1EnterData();
    BuildGraph();
    InitializeMatching();
    Stage1OutputData();

    Stage1Cleanup();

    Stage2EnterData();
    BuildGraph();
    InitializeMatching();
    Stage2OutputData();

    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//