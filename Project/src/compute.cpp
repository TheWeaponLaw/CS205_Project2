#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>
#include "../include/Calculator.h"

int finalDot = 0;
string string1;
string string2;
bool sim = true;

string clearBackZero(string sample1)
{
    if (judgeDou(sample1))
    {
        for (int i = sample1.size() - 1; i >= 0; i--)
        {
            if (sample1[i] != '0')
            {
                sample1 = sample1.substr(0, i + 1);
                break;
            }
            if (i == 0)
            {
                sample1 = "0";
                break;
            }
        }
    }
    if (sample1.at(sample1.size() - 1) == '.')
    {
        sample1.erase(sample1.size() - 1, 1);
    }
    return sample1;
}

string clearFrontZero(string sample1)
{
    for (int i = 0; i < sample1.size(); i++)
    {
        if (sample1[i] != '0')
        {
            if (sample1[i] == '.')
            {
                sample1 = sample1.substr(i - 1, sample1.size());
            }
            else
            {
                sample1 = sample1.substr(i, sample1.size());
            }
            break;
        }
        if (i == sample1.size() - 1)
        {
            sample1 = "0";
            break;
        }
    }
    return sample1;
}

int judgeDou(string sample) //找到double的点的位置
{
    for (int i = 0; i < (int)sample.size(); i++)
    {
        if (sample.at(i) == '.')
        {
            return sample.size() - i - 1; //从后往前数小数点的位置
        }
    }
    return 0;
}

//判断是否为整数
bool judgeInt(string sample)
{
    bool numExist = false;
    for (int i = 0; i < (int)sample.size(); i++)
    {
        switch (sample.at(i))
        {
        case '+':
        case '-':
            if (i != 0)
            {
                return false;
            }
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            numExist = true;
            break;
        default:
            return false;
        }
    }
    return numExist;
}

string bigMul(string sample1, string sample2, int dotPos)
{
    bool sign = true; //先去除符号位，多一个负号符号变一次
    if (sample1.at(0) == '+')
    {
        sample1.erase(0, 1);
    }
    else if (sample1.at(0) == '-')
    {
        sample1.erase(0, 1);
        sign = !sign;
    }

    if (sample2.at(0) == '+')
    {
        sample2.erase(0, 1);
    }
    else if (sample2.at(0) == '-')
    {
        sample2.erase(0, 1);
        sign = !sign;
    }

    int container[(sample1.size() + sample2.size())]; //最大可能值
    for (int i = 0; i < (int)(sample1.size() + sample2.size()); i++)
    {
        container[i] = 0; //赋值，避免随机值
    }
    for (int i = sample1.size() - 1; i >= 0; i--)
    {
        for (int j = sample2.size() - 1; j >= 0; j--)
        {
            container[sample1.size() + sample2.size() - 2 - i - j] +=
                (sample1.at(i) - '0') * (sample2.at(j) - '0'); //反向填充所乘数值
        }
    }
    for (int i = 0; i < (int)(sample1.size() + sample2.size()); i++)
    {
        if (container[i] >= 10)
        {
            container[i + 1] += container[i] / 10;
            container[i] = container[i] % 10; //进行进位
        }
    }
    bool zero = true;
    string answer;
    for (int i = sample1.size() + sample2.size() - 1; i >= 0; i--)
    {
        if (i == dotPos - 1)
        {
            answer.append(".");
            zero = false;
        }
        if (!zero || container[i] != 0)
        {
            zero = false; //去零，特殊情况后补零
            answer.append(to_string(container[i]));
        }
    }
    if (!sign)
    {
        answer.insert(0, "-");
    }
    return answer;
}

string dealDou(string sample, int position)
{
    if (position != 0)
    {
        return sample = sample.erase(sample.size() - position - 1, 1);
    }
    else
    {
        return sample;
    }
}

string computeDou(string str1, string str2, int douPos1, int douPos2)
{

    string sample1 = dealDou(std::move(str1), douPos1);
    string sample2 = dealDou(std::move(str2), douPos2);
    string answer = bigMul(sample1, sample2, douPos1 + douPos2);

    bool sign = answer.at(0) == '-' ? 1 : 0;
    if (answer.find(".", 0) == sign)
    {
        answer.insert(sign, "0"); //判断有无把“.”前面的0也去掉了，去掉了补上
    }
    if (answer.at(answer.size() - 1) == '.')
    {
        answer.erase(answer.size() - 1, 1); //统一整数和小数，整数后面会多加一个"."，修复
    }
    answer = clearBackZero(answer);
    return answer;
}

string mul(const string &sample1, const string &sample2)
{
    finalDot = 0;
    return computeDou(sample1, sample2, judgeDou(sample1), judgeDou(sample2));
}

void dealString(string sample1, string sample2, bool *sign1, bool *sign2)
{
    int dot1 = judgeDou(sample1);
    int dot2 = judgeDou(sample2);
    string1 = dealDou(sample1, dot1);
    string2 = dealDou(sample2, dot2);

    if (dot1 > dot2 && sim)
    {
        string2.append(dot1 - dot2, '0');
        finalDot = dot1;
    }
    else if (sim)
    {
        string1.append(dot2 - dot1, '0');
        finalDot = dot2;
    }

    if (sample1.at(0) == '-')
    {
        *sign1 = false;
        string1.erase(0, 1);
    }
    if (sample2.at(0) == '-')
    {
        *sign2 = false;
        string2.erase(0, 1);
    }
}

bool compStr()
{
    if (string1.size() < string2.size() || (string1.size() == string2.size() && string1 < string2))
    {
        return true;
    }
    return false;
}

bool swapStr(bool *sign1, bool *sign2)
{
    if (compStr())
    {
        swap(string1, string2);
        swap(sign1, sign2);
        return true;
    }
    return false;
}

string pureAdd(string sample1, string sample2)
{
    finalDot = 0;
    bool sign1 = true;
    bool sign2 = true;
    bool *p1 = &sign1;
    bool *p2 = &sign2;
    sim = true;
    dealString(std::move(sample1), std::move(sample2), p1, p2);
    swapStr(p1, p2);
    int dif = string1.size() - string2.size();
    int add = 0;
    int thisBit = 0;
    for (int i = string1.size() - 1; i >= 0; i--)
    {
        if (i >= dif)
        {
            thisBit = string1[i] + string2[i - dif] - 2 * '0' + add;
        }
        else
        {
            thisBit = string1[i] - '0' + add;
        }
        add = thisBit / 10;
        thisBit = thisBit % 10;
        string1[i] = thisBit + '0';
        if (i <= dif && add == 0)
        {
            break;
        }
        if (i == 0 && add == 1)
        {
            string1.insert(0, "1");
        }
    }
    if (finalDot != 0)
        string1.insert(string1.size() - finalDot, ".");
    string1 = clearFrontZero(string1);
    string1 = clearBackZero(string1);
    if (!sign1)
    {
        string1.insert(0, "-");
    }
    return string1;
}

string pureMinus(string sample1, string sample2)
{
    finalDot = 0;
    bool sign1 = true;
    bool sign2 = true;
    bool *p1 = &sign1;
    bool *p2 = &sign2;
    sim = true;
    dealString(std::move(sample1), std::move(sample2), p1, p2);
    sign1 = swapStr(p1, p2) ? !sign1 : sign1;
    int dif = string1.size() - string2.size();
    int minus = 0;
    int thisBit = 0;
    for (int i = string1.size() - 1; i >= 0; i--)
    {
        if (i >= dif)
        {
            thisBit = string1[i] - string2[i - dif] + minus;
        }
        else
        {
            thisBit = string1[i] - '0' + minus;
        }
        minus = (thisBit < 0) ? -1 : 0;
        thisBit = (thisBit < 0) ? thisBit + 10 : thisBit;
        string1[i] = thisBit + '0';
        if (i <= dif && minus == 0)
        {
            break;
        }
    }
    if (finalDot != 0)
        string1.insert(string1.size() - finalDot, ".");
    string1 = clearFrontZero(string1);
    string1 = clearBackZero(string1);
    if (!sign1)
    {
        string1.insert(0, "-");
    }
    return string1;
}

string divide(const string &sample1, const string &sample2)
{
    int final_Dot_Div = 0;
    bool sign1 = true;
    bool sign2 = true;
    bool *p1 = &sign1;
    bool *p2 = &sign2;
    sim = false;
    dealString(sample1, sample2, p1, p2);
    final_Dot_Div += judgeDou(sample2) - judgeDou(sample1);
    string1 = clearFrontZero(string1);
    string2 = clearFrontZero(string2);
    final_Dot_Div += string1.size() - string2.size();
    vector<char> result;
    if (!compStr()) //判断string1和string2处理完后的长度，先算string1>string2;
    {
        string2.append(string1.size() - string2.size(), '0');
    }
    else
    {
        string1.append(string2.size() - string1.size(), '0');
    }
    char temp = 0;
    bool flag = false;
    while (final_Dot_Div >= -30 && string1 != "0")
    {
        while (!compStr())
        {
            string1 = pureMinus(string1, string2);
            temp++;
            flag = true;
        }
        if (flag)
            result.push_back(temp);
        temp = 0;
        if (string1.size() && string1 != "0")
        {
            string1.append("0");
            final_Dot_Div--;
        }
    }
    final_Dot_Div = final_Dot_Div == -31 ? -30 : final_Dot_Div;
    string str;
    transform(result.begin(), result.end(), back_inserter(str), [](char c)
              { return c + '0'; });

    if (final_Dot_Div >= 0)
    {
        str.append(final_Dot_Div, '0');
    }
    else
    {
        if (abs(final_Dot_Div) >= str.size())
        {
            str.insert(0, -final_Dot_Div - str.size() + 1, '0');
            str.insert(1, ".");
        }
        else
        {
            str.insert(str.size() + final_Dot_Div, ".");
        }
    }
    if (sign1 ^ sign2)
    {
        str.insert(0, "-");
    }
    return str;
}

string mod(string sample1, string sample2)
{
    int final_Dot_Div = 0;
    int left = 0;
    bool sign1 = true;
    bool sign2 = true;
    bool *p1 = &sign1;
    bool *p2 = &sign2;
    sim = false;
    dealString(sample1, sample2, p1, p2);
    final_Dot_Div += string1.size() - string2.size() - judgeDou(sample1) + judgeDou(sample2);
    left += judgeDou(sample1);
    if (!compStr()) //判断string1和string2处理完后的长度，先算string1>string2;
    {
        string2.append(string1.size() - string2.size(), '0');
    }
    else
    {
        left += string2.size() - string1.size();
        string1.append(string2.size() - string1.size(), '0');
    }
    while (final_Dot_Div >= 0 && string1 != "0")
    {
        while (!compStr())
        {
            string1 = pureMinus(string1, string2);
        }
        if (string1.size() && string1 != "0")
        {
            string1.append("0");
            final_Dot_Div--;
            left++;
        }
    }
    if (left >= string1.size())
    {
        string1.insert(0, left - string1.size() + 1, '0');
        string1.insert(1, ".");
    }
    else if (left != 0)
    {
        string1.insert(string1.size() - left, ".");
    }
    //清除后面的0；
    string1 = clearBackZero(string1);
    if (!sign1 && string1 != "0")
    {
        string1.insert(0, "-");
    }
    return string1;
}

string factorial(string sample1)
{
    string temp = sample1;
    string result = "1";
    while (temp != "0")
    {
        result = mul(temp, result);
        temp = pureMinus(temp, "1");
    }
    return result;
}

string power(string sample1, string sample2)
{
    string result = "1";
    if (sample2 == "0")
    {
        return sample1;
    }

    while (sample2 != "0")
    {
        if (sample2[0] != '-')
        {
            result = mul(result, sample1);
            sample2 = pureMinus(sample2, "1");
        }
        else
        {
            result = divide(result, sample1);
            sample2 = pureMinus("1", sample2);
        }
    }
    return result;
}

bool comp(string sample1, string sample2)
{
    string temp1 = sample1;
    string temp2 = sample2;
    if (temp1.at(0) == '0')
    {
        temp1.erase(0, 1);
    }
    if (temp2.at(0) == '0')
    {
        temp2.erase(0, 1);
    }
    int dot1 = judgeDou(temp1);
    int dot2 = judgeDou(temp2);
    int int_length1 = (dot1 == 0) ? (int)temp1.size() : (int)temp1.size() - dot1 - 1;
    int int_length2 = (dot2 == 0) ? (int)temp2.size() : (int)temp2.size() - dot2 - 1;
    string int1 = temp1.substr(0, int_length1);
    string int2 = temp2.substr(0, int_length2);
    if (((int_length1 > int_length2)) || ((int_length1 == int_length2) && (int1 > int2)))
    {
        return true;
    }
    else if (dot1 == 0 || dot2 == 0)
    {
        if (dot2 == 0)
        {
            return true;
        }
        else if (dot1 == 0 && dot2 != 0)
        {
            return false;
        }
    }
    else
    {
        string double1 = temp1.substr(int_length1 + 1, temp1.size());
        string double2 = temp2.substr(int_length2 + 1, temp2.size());
        if (double1 >= double2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

string sqrt(string sample1)
{
    string x_next = sample1;
    string temp;
    string dif = "1";
    while (comp(dif, "0.0001"))
    {
        temp = x_next;
        x_next = divide((pureAdd(x_next, divide(sample1, x_next))), "2");
        dif = pureMinus(temp, x_next);
    }
    return x_next;
}
