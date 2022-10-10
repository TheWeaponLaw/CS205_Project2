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

        calculator.calculator();
    }
    return 0;
}
