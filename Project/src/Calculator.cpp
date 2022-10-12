//
// Created by 武器法 on 2022/10/7.
//

#include "../include/Calculator.h"
#include <iostream>

using namespace std;
enum
{
    Level_0 = 0,
    Level_1 = 1,
    Level_2 = 2,
    Level_3 = 3,
    Level_4 = 4,
    Level_5 = 5
};

int Calculator::opeLevel(char ope)
{
    switch (ope)
    {
    case '(':
    case '[':
    case '{':
    case '&':
    case '|':
        return Level_1;
    case '+':
    case '-':
        return Level_2;
    case '*':
    case '/':
    case '%':
        return Level_3;
    case '^':
    case '!':
        return Level_4;
    case ')':
    case '}':
    case ']':
        return Level_5;
    default:
        return Level_0;
    }
}

bool judge(string sample)
{
    for (size_t i = 0; i < sample.size(); i++)
    {
        if (!((sample.at(i) >= 'a' && sample.at(i) <= 'z') || (sample.at(i) >= 'A' && sample.at(i) <= 'Z')))
        {
            return false;
        }
    }
    return true;
}

void Calculator::genVar()
{
    string temp = expression;
    while (temp.find(" ") != string::npos)
    {
        temp.erase(temp.find(" "), 1);
    }
    string name = temp.substr(0, temp.find('='));
    string num;
    if (temp.size() == temp.find('='))
    {
        cout << "Wrong assign expression!" << endl;
        return;
    }
    else
    {
        num = temp.substr(temp.find('=') + 1, temp.size() - temp.find('='));
    }
    if (judge(name) && name != "sqrt" && name != "abs")
    {
        expression = num;
        num = calculator();
        if (num == "")
        {
            cout << endl;
        }
        else if (var.find(name) != var.end())
        {
            var[name] = num;
        }
        else
        {
            var.insert(make_pair(name, num));
        }
    }
    else
    {
        cout << "Incorrect expression" << endl;
    }
}

//表达式支持 + - * / % ! ^ () [] {} sqrt() abs()数字
void Calculator::format()
{
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] == '+' || expression[i] == '-')
        {
            if (i == 0)
            {
                expression.insert(0, 1, '0');
            }
            else if (expression[i - 1] == '(' || expression[i - 1] == '[' || expression[i - 1] == '{')
            {
                expression.insert(i, 1, '0');
            }
        }
    }
}
bool maxSignal = false;
bool separateSignal = false;
string Calculator::calculator()
{
    clear();
    format();
    try
    {
        for (size_t i = 0; i < expression.size(); i++)
        {
            switch (expression[i])
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '!':
            case '^':
            case '%':
                if (opeStack.empty() || opeLevel(opeStack.top()) < opeLevel(expression[i]))
                {
                    opeStack.push(expression[i]);
                }
                else
                {
                    while (!opeStack.empty() && opeLevel(opeStack.top()) >= opeLevel(expression[i]))
                    {
                        calNum();
                        opeStack.pop();
                    }
                    opeStack.push(expression[i]);
                }
                break;
            case '(':
            case '[':
            case '{':
                opeStack.push(expression[i]);
                break;
            case ')':
                while (!opeStack.empty() && opeStack.top() != '(')
                {
                    calNum();
                    opeStack.pop();
                }
                if (!opeStack.empty() && opeStack.top() == '(')
                {
                    opeStack.pop();
                }
                break;
            case ']':
                while (!opeStack.empty() && opeStack.top() != ']')
                {
                    calNum();
                    opeStack.pop();
                }
                if (!opeStack.empty() && opeStack.top() == ']')
                {
                    opeStack.pop();
                }
                break;
            case '}':
                while (!opeStack.empty() && opeStack.top() != '}')
                {
                    calNum();
                    opeStack.pop();
                }
                if (!opeStack.empty() && opeStack.top() == '}')
                {
                    opeStack.pop();
                }
                break;
            case ' ':
                break;
            default:
                if (expression[i] >= '0' && expression[i] <= '9')
                {
                    string num;
                    num += expression[i];
                    while (i + 1 < expression.length() &&
                           ((expression[i + 1] >= '0' && expression[i + 1] <= '9') ||
                            expression[i + 1] == '.' || expression[i + 1] == ' '))
                    {
                        if (expression[i + 1] == ' ')
                        {
                            i++;
                            continue;
                        }
                        num += expression[i + 1];
                        i++;
                    }
                    if (judgeInt(num) || judgeDou(num))
                    {
                        for (int j = 0; j < num.size(); j++)
                        {
                            if (num[j] != '0')
                            {
                                if (num[j] == '.')
                                {
                                    num = num.substr(j - 1, num.size());
                                }
                                else
                                {
                                    num = num.substr(j, num.size());
                                }
                                break;
                            }
                            if (j == num.size() - 1)
                            {
                                num = "0";
                                break;
                            }
                        }
                        numStack.push(num);
                    }
                    else
                    {
                        throw "Not a correct expression!";
                    }
                }
                else if (expression[i] == 's')
                {
                    if (expression.substr(i, 5) == "sqrt(")
                    {
                        opeStack.push('(');
                        opeStack.push('&');
                        i += 4;
                    }
                }
                else if (expression[i] == 'a')
                {
                    if (expression.substr(i, 4) == "abs(")
                    {
                        opeStack.push('(');
                        opeStack.push('|');
                        i += 3;
                    }
                }
                else if (expression[i] == 'm')
                {
                    if (expression.substr(i, 4) == "max(")
                    {
                        opeStack.push('(');
                        opeStack.push('#');
                        i += 3;
                        maxSignal = true;
                    }
                }
                else if (expression[i] == ',')
                {
                    if (maxSignal && !separateSignal)
                    {
                        separateSignal = true;
                    }
                    else
                    {
                        throw "Wrong expression!";
                    }
                }
                else if ((expression[i] >= 'a' && expression[i] <= 'z') ||
                         (expression[i] >= 'A' && expression[i] <= 'Z'))
                {
                    string name;
                    name += expression[i];
                    while (i + 1 < expression.size() && ((expression[i + 1] >= 'a' && expression[i + 1] <= 'z') ||
                                                         (expression[i + 1] >= 'A' && expression[i + 1] <= 'Z')))
                    {
                        name += expression[i + 1];
                        i++;
                    }
                    if (!(var.find(name) == var.end()))
                    {
                        numStack.push(var[name]);
                    }
                    else
                    {
                        throw "Don't have this variable!";
                    }
                }
                else
                {
                    throw "Not a correct expression!";
                }
            }
        }
        while (!opeStack.empty())
        {
            switch (opeStack.top())
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '!':
            case '^':
            case '%':
            case '&':
            case '|':
            case '#':
                calNum();
                opeStack.pop();
                break;
            case ')':
            case ']':
            case '}':
                opeStack.pop();
                break;
            }
        }
        if (!numStack.empty())
        {
            string temp = numStack.top();
            numStack.pop();
            return temp;
        }
    }
    catch (const char *msg)
    {
        cout << msg;
        return "";
    }
    return "";
}

void Calculator::calNum()
{
    string s1;
    string s2;
    switch (opeStack.top())
    {
    case '+':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            if ((s1.at(0) != '-' && s2.at(0) != '-') || (s1.at(0) == '-' && s2.at(0) == '-'))
                numStack.push(pureAdd(s1, s2));
            else
            {
                if (s1.at(0) == '-' && s2.at(0) != '-')
                    numStack.push(pureMinus(s2, s1.erase(0, 1)));
                else if (s1.at(0) != '-' && s2.at(0) == '-')
                    numStack.push(pureMinus(s1, s2.erase(0, 1)));
            }
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '-':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            if ((s1.at(0) != '-' && s2.at(0) != '-') || (s1.at(0) == '-' && s2.at(0) == '-'))
                numStack.push(pureMinus(s1, s2));
            else
            {
                if (s1.at(0) == '-' && s2.at(0) != '-')
                    numStack.push(pureAdd(s2, s1.insert(0, "-")));
                else if (s1.at(0) != '-' && s2.at(0) == '-')
                    numStack.push(pureAdd(s1, s2.erase(0, 1)));
            }
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '*':
        if (numStack.size() >= 2)
        {
            s1 = numStack.top();
            numStack.pop();
            s2 = numStack.top();
            numStack.pop();
            numStack.push(mul(s1, s2));
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '/':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            if (s1 == "0" && s2 == "0")
            {
                throw "NAN";
            }
            else if (s2 == "0")
            {
                throw "Infinite";
            }
            numStack.push(divide(s1, s2));
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '!':
        if (!numStack.empty())
        {
            s1 = numStack.top();
            numStack.pop();
            numStack.push(factorial(s1));
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '^':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            numStack.push(power(s1, s2));
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '%':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            if (s2 == "0")
            {
                throw "You can't n%0";
            }
            numStack.push(mod(s1, s2));
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '&':
        if (!numStack.empty())
        {
            s1 = numStack.top();
            numStack.pop();
            if (s1[0] == '-')
            {
                throw "You can't sqrt minus!";
            }
            // numStack.push(radical(s1,"0.5"));
            numStack.push(sqrt(s1));
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '|':
        if (!numStack.empty())
        {
            s1 = numStack.top();
            numStack.pop();
            if (s1[0] == '-')
            {
                numStack.push(s1.erase(0, 1));
            }
            else
            {
                numStack.push(s1);
            }
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    case '#':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            numStack.push(max(s1, s2));
            separateSignal = false;
            maxSignal = false;
        }
        else
        {
            throw "Incorrect expression!";
        }
        break;
    default:
        throw "Wrong expression!";
        break;
    }
}

void Calculator::clear()
{
    while (!numStack.empty())
        numStack.pop();
    while (!opeStack.empty())
        opeStack.pop();
}