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

        This file contains the core data type and its corresponding operations

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
#pragma once


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
#define FOR(i, x, y) for(int i=x; i<=(int)y; ++i)
#define FORl(i, x, y) for(int i=x; i<(int)y; ++i)
#define FORb(i, x, y) for(int i=x; i>=(int)y; --i)
#define FORlb(i, x, y) for(int i=x; i>(int)y; --i)


//=====================================
//Constants
vector<wstring> Morning({L"cả ngày", L"sáng+chiều", L"sáng và chiều", L"sáng"});
vector<wstring> Afternoon({L"cả ngày", L"sáng+chiều", L"sáng và chiều", L"chiều"});



//---------------------------------------------------------------------------------
//Data defs
struct Class_InputData_Type
{
    typedef vector<wstring> vwstr;
    typedef vector<bool> vb;
    typedef vector<int> vi;
    typedef vector<vb> vvb;

    wstring name, school;
    vi date_order;
    vvb available;
    int qty;

    Class_InputData_Type()
    {
        date_order = vi({0, 0, 0, 2, 4, 6, 0, 0, 0, 0});
        available = vvb(10, vb(6, 0));
        name = school = L"";
        qty = 0;
    }
    Class_InputData_Type(wstring inputted)
    {
        date_order = vi({0, 0, 0, 2, 4, 6, 0, 0, 0, 0});
        available = vvb(10, vb(6, 0));
        vwstr word = CSVInput(inputted);
        

        FORl(i, 3, word.size()) for (auto& ch : word[i]) ch = towlower(ch);
        name = word[0];
        school = word[1];
        qty = stoi(word[2]);


        FORl(i, 3, word.size())
        {
            bool special = 0;
            int date = date_order[i];

            //Morning
            if (inPool(word[i], Morning)) available[date][1] = available[date][2] = available[date][3] = 1;

            //Afternoon
            if (inPool(word[i], Afternoon)) available[date][4] = available[date][5] = 1;

            //Other cases
            if (word[i][0] == L'_')
            {
                FORl(k, 1, word[i].size()) if (isdigit(word[i][k])) available[date][word[i][k] - '0'] = 1;
                //break;
            }
        }
    }


    bool operator< (const Class_InputData_Type& oth) const
    {
        return make_tuple(qty, school, name) < make_tuple(oth.qty, oth.school, oth.name);
    }
};
struct Slots_InputData_Type
{
    typedef vector<wstring> vwstr;

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

        seed = rand();
        week = _week;
        date = _date;
        shift_id = _shift_id;
        match_id = _match_id;
        information = _information;
    }
    Slots_InputData_Type(wstring inputted)
    {
        srand(time(NULL));

        vwstr word = CSVInput(inputted);
        seed = rand();
        int cnt = 0;

        week = stoi(word[0]);
        date = stoi(word[1]);
        shift_id = stoi(word[2]);
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


//---------------------------------------------------------------------------------
//Data-related typedef
typedef vector<Class_InputData_Type>                               Class_InputData_Type_Pool;
typedef map<Class_InputData_Type, int>                             Class_InputData_Type_Encode;
typedef map<int, Class_InputData_Type>                             Class_InputData_Type_Decode;       //Vertex -> Data


typedef vector<Slots_InputData_Type>                               Slots_InputData_Type_Pool;
typedef map<Slots_InputData_Type, int>                             Slots_InputData_Type_Encode;
typedef map<int, Slots_InputData_Type>                             Slots_InputData_Type_Decode;       //Vertex -> Data


//---------------------------------------------------------------------------------
//Data operations
void EnterClass(wstring str, Class_InputData_Type_Pool& _A, Class_InputData_Type_Encode& _Class_Encode, Class_InputData_Type_Decode& _Class_Decode)
{
    if (_Class_Encode.count(Class_InputData_Type(str))) {
        wcerr << str << el; return;
    }

    _A.emplace_back(str);
    _Class_Encode[_A.back()] = _A.size();
    _Class_Decode[_A.size()] = _A.back();
}
void EnterSlots(wstring str, Slots_InputData_Type_Pool& _B, Slots_InputData_Type_Encode& _Slots_Encode, Slots_InputData_Type_Decode& _Slots_Decode)
{
    Slots_InputData_Type test_slot(str);

    int limit = test_slot.week >= 44 ? 3 : 2;
    FOR(i, 1, limit)
    {
        _B.emplace_back(str);
        _B.back().match_id = i;
        _Slots_Encode[_B.back()] = _B.size();
        _Slots_Decode[_B.size()] = _B.back();
    }
}


