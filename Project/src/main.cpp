#include <iostream>
#include "../include/Calculator.h"

using namespace std;

int main()
{
    Calculator calculator;
    while (true)
    {
        getline(cin, calculator.expression);
        if (std::equal(calculator.expression.begin(), calculator.expression.end(), "\n"))
        {
            return 0;
        }
        if (calculator.expression == "clear")
        {
            calculator.var.clear();
        }
        else if (calculator.expression.find("=") == string::npos)
        {
            cout << calculator.calculator() << endl;
        }
        else
        {
            calculator.genVar();
        }
    }
    return 0;
}
//尝试提交修改