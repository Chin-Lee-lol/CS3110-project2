#ifndef Convertor_H
#define Convertor_H
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

struct floatNum { // so we can return both float number and indicater says its float number or not
    float num = 0;
    bool isNum = true;
};

class Convertor // just project one in other file lol so main file not too messy (i hope)
{
public:
    Convertor() {};
    floatNum FPLConvertor(string input);
};

#endif

string LetterCheck(string input, char check, int size)
{
    int a = input.find(check);
    if (a != -1)
    {
        cout << "\nDecimal number cannot contain " << check << " letter\n";
        return "";
    }
    return input;
}
string FloatTypeSuffixChecker(string input, char check, int size)
{
    int f = input.find(check); // simply remove f F d D from the string
    if (f != -1)
        if (f == size - 1) // if f is last char, then cool
            input.erase(f, 1);
        else
        {
            cout << "\nThe " << check << " notation in wrong location\n";
            return ""; // wrong notation
        }
    f = input.find(check); // simply remove f F d D from the string
    if (f != -1)
    {
        cout << "\nThere are multiple " << check << " notation in the string\n";
        return "";
    }
    return input; // cool
}

float StringToFloat(string input, bool hex)
{
    float sum = 0; bool period = false;
    int dot = input.find('.');
    if (dot != -1) // deal with .
    {
        input.erase(dot, 1);
        period = true;
    }
    int dotpos = dot;
    dot = input.find('.');
    if (dot != -1) // if theres one more . in string => nono
    {
        cout << "\nString contains more than one '.'\n";
        return 0;
    }
    int n = input.size() - 1, temp; // to help calculate position
    for (int i = 0; i < input.size(); i++)
    {
        switch (input.at(i)) // assign value corresponsively to the character
        {
        case 'f': case 'F':temp = 15; break;
        case 'e': case 'E':temp = 14; break;
        case 'd': case 'D':temp = 13; break;
        case 'c': case 'C':temp = 12; break;
        case 'b': case 'B':temp = 11; break;
        case 'a': case 'A':temp = 10; break;
        case '9': temp = 9; break;
        case '8': temp = 8; break;
        case '7': temp = 7; break;
        case '6': temp = 6; break;
        case '5': temp = 5; break;
        case '4': temp = 4; break;
        case '3': temp = 3; break;
        case '2': temp = 2; break;
        case '1': temp = 1; break;
        case '0': temp = 0; break;
        default: cout << "\nThe '" << input.at(i) << "' character is not valid\n";
            return 0;
        };
        if (hex) // if it is hexadecimal multiply 16 for position else 10
            sum += temp * pow(16, n);
        else
            sum += temp * pow(10, n);
        n--;
    }
    if (period) // if theres dot, divide according to dot position
        sum /= pow(10, input.length() - dotpos);
    return sum;
}

floatNum Convertor::FPLConvertor(string input)
{
    floatNum fnum;
    bool negative = false;
    float output = 0;
    int n = input.length();
    int underscore = input.find('_');
    string og = input;
    while (underscore != -1) // simply remove _ notation
    {
        input.erase(underscore, 1);
        underscore = input.find('_');
    }
    if (input.at(0) == '-') // check negative sign
    {
        negative = true;
        input.erase(0, 1); // remove - sign
    }
    if (input.substr(0, 2).compare("0x") == 0) //check if is hexadecimal
    {
        input.erase(0, 2); // remove 0x from the string
        output = StringToFloat(input, true);
    }
    else // it is not hexadecimal
    {
        bool Echeck = false;
        bool Eneg = false;
        float power = 0;
        int check1 = input.find('f'), check2 = input.find('F'), check3 = input.find('d'), check4 = input.find('D'),
            check5 = input.find('e'), check6 = input.find('E'), check7 = input.find('.');
        if (check1 == -1 && check2 == -1 && check3 == -1 && check4 == -1 && check5 == -1 && check6 == -1 && check7 == -1)
        {
            cout << endl;
            cout << og << " is not a float number.\n";
            fnum.isNum = false; // this is not floating number
            return fnum;
        }
        input = FloatTypeSuffixChecker(input, 'f', n);
        input = FloatTypeSuffixChecker(input, 'd', n);
        input = FloatTypeSuffixChecker(input, 'D', n);
        input = FloatTypeSuffixChecker(input, 'F', n);
        input = LetterCheck(input, 'a', n);
        input = LetterCheck(input, 'A', n);
        input = LetterCheck(input, 'b', n);
        input = LetterCheck(input, 'B', n);
        input = LetterCheck(input, 'c', n);
        input = LetterCheck(input, 'C', n);
        if (input.compare("") == 0)
        {
            fnum.isNum = false; // this is not floating number
            return fnum;
        }

        int e = input.find('e'), E = input.find('E'), index; // check if theres e/E notation in string
        if (e != -1 || E != -1)
        {
            string exponent;
            if (e != -1)
                index = e;
            else
                index = E;
            input.erase(index, 1); // remove e/E notation
            if (index == input.size())
            {
                cout << "\nThere must be a number behind exponential notation\n";
                fnum.isNum = false; // this is not floating number
                return fnum;
            }
            if (input.at(index) == '+')
                input.erase(index, 1);
            if (input.at(index) == '-')
            {
                input.erase(index, 1);
                Eneg = true;
            }
            e = input.find('e');
            E = input.find('E');
            if (e != -1 || E != -1) // if theres more than 1 e/E => nono
            {
                cout << "\nThere are more than one e notation in the string\n";               
                fnum.isNum = false; // this is not floating number
                return fnum;                
            }
            exponent = input.substr(index, input.size() - index); // store number after e/E in another string
            input.erase(index, input.size() - index); // erase number in exponent part    
            int dot = exponent.find('.');
            if (dot != -1) // if theres a dot in exponential part => nono
            {
                cout << "\nThere is '.' in the exponential part\n";
                fnum.isNum = false; // this is not floating number
                return fnum;
            }
            power = StringToFloat(exponent, false);
            if (Eneg)
                power *= -1;
        }
        output = StringToFloat(input, false);
        output = output * pow(10, power);
    }
    if (negative)
        output *= -1;
    fnum.num = output;
    return fnum;
}
