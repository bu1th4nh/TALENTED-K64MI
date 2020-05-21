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

        This file contains utilities for main program such as debugging, find tokens, etc....

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
locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto timeStart = chrono::steady_clock::now();
auto timeEnd = chrono::steady_clock::now();
auto Full_timeStart = chrono::steady_clock::now();
auto Full_timeEnd = chrono::steady_clock::now();

//---------------------------------------------------------------------------------
template<class T> vector<T> CSVInput(T inputString)
{
	vector<T> ret;
    T tokens;

    for (auto c : inputString)
    {
        if (c == com) ret.push_back(tokens), wcerr << tokens << el, tokens.clear();
        else tokens += c;
    }
    ret.push_back(tokens);


    return ret;
}
template<class T> bool inPool(T val, vector<T>& vect)
{
    for (auto s : vect) if (val.find(s) != -1) return 1;
    return 0;
}


//---------------------------------------------------------------------------------
//Debugging
void Debug()
{
    //wofstream DEBUG("debug.csv");  DEBUG.imbue(loc);

    /*
    for (auto x : A)
    {
        DEBUG << x.name << com << x.monday << com << x.wednesday << com << x.friday << el;
    }

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

