#include <iostream>
#include "../include/Calculator.h"

using namespace std;

int main()
{
    Calculator calculator;
    while (true)
    {
        getline(cin, calculator.expression);
        if (calculator.expression == "exit")
        {
            return 0;
        }
        else if (calculator.expression == "clear")
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
