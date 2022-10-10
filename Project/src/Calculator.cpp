//
// Created by 武器法 on 2022/10/7.
//

#include "../include/Calculator.h"
#include <iostream>
#include <cmath>

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

//表达式支持 + - * / % ! ^ () [] {} 数字
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

void Calculator::calculator()
{
    clear();
    format();
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
                    cout << "Invalid input!" << endl;

                    return;
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
            else
            {
                cout << "Not a correct expression!" << endl;
                return;
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
        cout << (numStack.top()) << endl;
        numStack.pop();
    }
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
            cout << "Incorrect expression!" << endl;
            return;
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
            cout << "Incorrect expression!" << endl;

            return;
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
            cout << "Incorrect expression!" << endl;

            return;
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
                cout << "NAN" << endl;

                return;
            }
            else if (s2 == "0")
            {
                cout << "Infinite" << endl;
                return;
            }
            numStack.push(divide(s1, s2));
        }
        else
        {
            cout << "Incorrect expression!" << endl;

            return;
        }
        break;
    case '!':
        if (!numStack.empty())
        {
            s1 = numStack.top();
            numStack.pop();
            if (s1 == "0")
            {
                cout << "You can't use 0!" << endl;
                return;
            }
            numStack.push(factorial(s1));
        }
        else
        {
            cout << "Incorrect expression!" << endl;
            return;
        }
        break;
    case '^':
        if (numStack.size() >= 2)
        {
            s2 = numStack.top();
            numStack.pop();
            s1 = numStack.top();
            numStack.pop();
            if (mod(s2, "1") != "0")
            {
                cout << "Sorry the programme can't support double now, we change it into int" << endl;
                numStack.push(power(s1, s2.substr(0, s2.size() - judgeDou(s2) - 1)));
            }
            else
            {
                numStack.push(power(s1, s2));
            }
        }
        else
        {
            cout << "Incorrect expression!" << endl;
            return;
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
                cout << "You can't n%0" << endl;
                return;
            }
            numStack.push(mod(s1, s2));
        }
        else
        {
            cout << "Incorrect expression!" << endl;
            return;
        }
        break;
    case '&':
        if (!numStack.empty())
        {
            s1 = numStack.top();
            numStack.pop();
            if (s1[0] == '-')
            {
                cout << "You can't sqrt minus!" << endl;
                return;
            }
            numStack.push(sqrt(s1));
        }
        else
        {
            cout << "Incorrect expression!" << endl;
            return;
        }
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