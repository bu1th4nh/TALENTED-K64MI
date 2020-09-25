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
#define OPTIONAL_FEATURE

//=====================================
//Macroes
#define sp ' '
#define el '\n'
#define task "TEST"
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

//#define DEBUG_ON


//=====================================
//Constants


const unordered_set<char> operators = {'(', ')', '!', '&', '|', '<', '>', '-'};
const unordered_map<string, int> x_ary_operators = {{"&", 2}, {"|", 2}, {"!", 1}, {"<->", 2}, {"->", 2}};
const unordered_map<string, int> priority_operators = {{"&", 1}, {"|", 2}, {"!", 3}, {"<->", -1}, {"->", 0}};
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

vector<string> infix_expr, postfix_expr, headings;
map<string, int> variable_list;
string input_expr;
int n, nVariables;
vvi result;


//=====================================
//Functions and procedures
//Enter expression
void Enter()
{
    string input;
	getline(cin, input);
	for(auto x: input) if(x != ' ') input_expr += string(1, x);
	n = input_expr.size();
	cerr << input_expr << el;
}

//Tokenization and Postfix Formation
void tokenizeInput()
{
    //Tokenize input
    FORl(i, 0, n) if(input_expr[i] != ' ') if(!operators.count(input_expr[i]))
    {
        //a variable detected
        string temp_var = "";
        while(1)
        {
            temp_var += input_expr[i];
            if(i + 1 >= n || operators.count(input_expr[i+1])) break;
            ++i;
        }
        variable_list.emplace(temp_var, 0);
        infix_expr.push_back(temp_var);
        continue;
    }
    else if(input_expr[i] != '<' && input_expr[i] != '-' && input_expr[i] != '>')
    {
        //regular operator detected
        infix_expr.emplace_back(string(1, input_expr[i]));
    }
    else
    {
        //"->" or "<->" detected
        if(input_expr[i] == '-') infix_expr.emplace_back("->"), i += 1;
        else infix_expr.emplace_back("<->"), i += 2;
    }
    nVariables = variable_list.size();


    #ifdef DEBUG_ON
        cerr << variable_list.size() << el;
        cerr << input_expr << el;
        for(auto x: variable_list) cerr << x.fi << sp;
        cerr << el;
        for(auto x: infix_expr) cerr << x;
        cerr << el;
    #endif // DEBUG_ON
}
void buildPostfixForm()
{
    stack<string> token_pool;
    for(string token: infix_expr)
    {
        if(token == "(") token_pool.emplace(token);
        else if(token == ")")
        {
            while(!token_pool.empty() && token_pool.top() != "(")
            {
                postfix_expr.emplace_back(token_pool.top());
                token_pool.pop();
            }
            if(!token_pool.empty()) token_pool.pop();
        }
        else if(priority_operators.count(token))
        {
            while(!token_pool.empty() && token_pool.top() != "(")
            {
                int stack_priority = priority_operators.at(token_pool.top());
                int token_priority = priority_operators.at(token);

                if(stack_priority >= token_priority)
                {
                    postfix_expr.emplace_back(token_pool.top());
                    token_pool.pop();
                }
                else break;
            }
            token_pool.emplace(token);
        }
        else postfix_expr.emplace_back(token);
    }
    while(!token_pool.empty()) postfix_expr.emplace_back(token_pool.top()), token_pool.pop();


    #ifdef DEBUG_ON
        for(auto x: postfix_expr) cerr << x << sp;
        cerr << el;
    #endif // DEBUG_ON
}


//Compute Results - Evaluation
int evalUnaryOperator(int A, const string &token)
{
    if(token == "!") return !(A);
}
int evalBinaryOperator(int L, int R, const string &token)
{
    if(token == "&") return (L && R);
    if(token == "|") return (L || R);
    if(token == "->") return (L && (!R)) ? 0 : 1;
    if(token == "<->") return (L == R);
}


//Compute Results - Configuration
void computeConfiguraton(ll config)
{
    //Result for single configuration
    vi cfg_result(nVariables, 0);


    //Config setup
    int cnt = 0;
    for(auto &x: variable_list)
    {
        x.se = cfg_result[cnt] = (config >> (nVariables - 1 - cnt)) & 1;
        ++cnt;
    }


    //Compute results
    stack<int> operand_pool;
    for(string token: postfix_expr)
    {
        if(!x_ary_operators.count(token)) operand_pool.emplace(variable_list.at(token));
        else if(x_ary_operators.at(token) == 1)
        {
            int A = operand_pool.top(); operand_pool.pop();
            operand_pool.push(evalUnaryOperator(A, token));
            cfg_result.push_back(operand_pool.top());
        }
        else if(x_ary_operators.at(token) == 2)
        {
            int R = operand_pool.top(); operand_pool.pop();
            int L = operand_pool.top(); operand_pool.pop();
            operand_pool.push(evalBinaryOperator(L, R, token));
            cfg_result.push_back(operand_pool.top());
        }
    }
    assert(!operand_pool.empty());



    //Load cfg. result into main result pool
    result.emplace_back(cfg_result);


    //Debug
    #ifdef DEBUG_ON
        cerr << "Config #" << setw(4) << config << ": \n";
        for(auto x: variable_list) cerr << x.se << sp; cerr << el;
        for(auto x: cfg_result) cerr << x << sp; cerr << el;
    #endif // DEBUG_ON
}
void computeOutputs()
{
    FORl(i, 0, (1 << nVariables)) computeConfiguraton(i);
}


//Output
void printHeadings()
{
    //Print title row for "table"
    stack<string> operand_pool;
    for(auto x: variable_list) headings.emplace_back(x.fi);
    for(string token: postfix_expr)
    {
        if(!x_ary_operators.count(token))
        {
            operand_pool.push(token);
        }
        else if(x_ary_operators.at(token) == 1)
        {
            string A = operand_pool.top(); operand_pool.pop();

            operand_pool.push(token + A);
            headings.emplace_back(operand_pool.top());
        }
        else if(x_ary_operators.at(token) == 2)
        {
            string R = operand_pool.top(); operand_pool.pop();
            string L = operand_pool.top(); operand_pool.pop();

            operand_pool.push("("+L+token+R+")");
            headings.emplace_back(operand_pool.top());
        }
    }
    assert(!operand_pool.empty());
}
void printResults()
{
    int k = headings.size();
    int sum_width = 3 * (k-1) + 4;
    string title = string("Test for logical expression: ") + input_expr;
    FORl(i, 0, k) sum_width += headings[i].size();

    //Print title rows
    int left_bound = (sum_width - 2 - title.size()) / 2;
    int remains = sum_width - 2 - title.size() - left_bound;
    cout << el << el;
    cout << "|" << string(sum_width-2 ,'=') << "|"  << el;
    cout << "|" << string(sum_width-2 ,' ') << "|"  << el;
    cout << "|" << string(left_bound, ' ') << title << string(remains, ' ') << "|" << el;    cout << "|" << string(sum_width-2 ,' ') << "|"  << el;

    //Print heading row
    cout << "|"; FORl(i, 0, k) cout << "=" << string(headings[i].size(), '=') << "=|" ; cout << el;
    cout << "| "; FORl(i, 0, k) cout << headings[i] << " | "; cout << el;
    cout << "|"; FORl(i, 0, k) cout << "=" << string(headings[i].size(), '=') << "=|" ; cout << el;

    //Print final output
    for(auto cfg_res: result)
    {
        cout << "| ";
        FORl(i, 0, k) cout << setw(headings[i].size()) << cfg_res[i] << " | ";
        cout << el;
    }

    //Print border
    cout << "|"; FORl(i, 0, k) cout << "=" << string(headings[i].size(), '=') << "=|" ; cout << el;


    cout << el << el << "Made w/ love by bu1th4nh. (c) 2020 bu1th4nh. Some rights reserved." << el;
}


//Solve 'em all!
void Solve()
{
    tokenizeInput();
    buildPostfixForm();
    computeOutputs();
    printHeadings();
    printResults();
}

//Main Procedure
int main()
{
    FILEOP();
    Enter();
    Solve();
    return 0;
}

//=============================================================================//
/**    CTB, you are always in my heart and in my code <3       #30yearsCTB    **/
//=============================================================================//
