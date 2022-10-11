#pragma once
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;
class Calculator
{
public:
    void format();
    string calculator();
    void calNum();
    int opeLevel(char ope);
    void clear();
    void genVar();

    stack<string> numStack;
    stack<char> opeStack;
    string expression;
    string stdExpr;
    unordered_map<string, string> var;
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
string radical(string sample1, string sample2);