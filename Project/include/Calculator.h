#pragma once
#include <string>
#include <stack>

using namespace std;
class Calculator
{
public:
    void format();
    void calculator();
    void calNum();
    int opeLevel(char ope);
    void clear();

    stack<string> numStack;
    stack<char> opeStack;
    string expression;
    string stdExpr;
};

string mul(const string &sample1, const string &sample2);
bool judgeInt(string sample);
int judgeDou(string sample);
string pureAdd(string sample1, string sample2);
string pureMinus(string sample1, string sample2);
string divide(const string &sample1, const string &sample2);
string mod(string sample1, string sample2);
string factorial(string sample1);
string power(string sample1, string sample2);
string sqrt(string sample1);