#pragma once
#include <string>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;
class Calculator
{
public:
    void format();          //整理表达式形式，在单个负号或正号前补零
    string calculator();    //放入数字栈和符号栈中，并将符号弹出，进行计算
    void calNum();          //符号对数字栈中的数字进行计算
    int opeLevel(char ope); //判断计算符号的优先级
    void clear();           //清除数字栈和符号栈
    void genVar();          //获得并保存变量

    stack<string> numStack;            //数字栈
    stack<char> opeStack;              //符号栈
    string expression;                 //输入表达式
    unordered_map<string, string> var; //记录变量的Hashmap,记录变量名称和数值
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
string max(string sample1, string sample2);