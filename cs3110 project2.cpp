#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Convertor.h"

int opFinder(string exp, bool findRight) // func to helps find operation
{
    if (findRight)
    {
        int pos = exp.find('/');
        if (pos != -1)
            return pos;
        pos = exp.find('*');
        if (pos != -1)
            return pos;
        pos = exp.find('+');
        if (pos != -1)
            if (exp.find('e') != pos - 1)   // if + or - is behind e/E, ignore it
                if(exp.find('E') != pos -1)
                    return pos;
        pos = exp.find('-');
        if (pos != -1)
            if (exp.find('e') != pos - 1)
                if (exp.find('E') != pos - 1)
                    return pos;
        return -1;
    }
    int pos = exp.find_last_of('/');
    if (pos != -1)
        return pos;
    pos = exp.find_last_of('*');
    if (pos != -1)
        return pos;
    pos = exp.find_last_of('+');
    if (pos != -1)
        if (exp.find_last_of('e') != pos - 1)
            if (exp.find_last_of('E') != pos - 1)
                return pos;
    pos = exp.find_last_of('-');
    if (pos != -1)
        if (exp.find_last_of('e') != pos - 1)
            if (exp.find_last_of('E') != pos - 1)
                return pos;
    return -1;
}

string Calculate(string l, string r, char op)
{
    Convertor C;
    floatNum f;
    float result, leftVal, rightVal;
    f = C.FPLConvertor(l);
    if (!f.isNum) // the number part is not floating point
    {
        cout << "\nThe \"" << l << "\" expression is not a floating point number\n";
        return " ";
    }
    leftVal = f.num;
    f = C.FPLConvertor(r);
    if (!f.isNum)
    {
        cout << "\nThe \"" << r << "\" expression is not a floating point number\n";
        return " ";
    }
    rightVal = f.num;
    switch (op) // simply evaluate at this point
    {
    case '/': result = leftVal / rightVal; break;
    case '*': result = leftVal * rightVal; break;
    case '+': result = leftVal + rightVal; break;
    case '-': result = leftVal - rightVal;
    }
    return to_string(result);
}

string Evaluate(string exp) // a function to evaluate the expression
{
    Convertor C;
    floatNum f;
    float sum = 0;
    if (opFinder(exp, true) == -1) // if no operation in this expression
    {
        f = C.FPLConvertor(exp);
        if (f.isNum)       
            return  to_string(f.num);
        
        cout << "\nThe " << exp << " expression is not a floating point number\n";
        return " ";
    } 
    while (opFinder(exp,true) != -1) // there is an expression, evaluate until none left
    {
        string l, r;
        int leftOP, rightOP;
        float leftVal, rightVal;
        int temp = 0;
        int op = exp.find('/');      
        if (op != -1)
        {
            l = exp.substr(0, op); // split string to left and right of the operation
            r = exp.substr(op + 1, exp.length());
            exp.erase(op, 1); // remove that operation from the string
            leftOP = opFinder(l, false); // check if theres operation in those strings
            rightOP = opFinder(r, true);
            if (leftOP != -1) // if there is, get the number part only
                l = l.substr(leftOP + 1, l.length());
            if (rightOP != -1)
                r = r.substr(0, rightOP);
            exp.erase(op - l.length(), op + r.length()); // remove right and left number from the exp
            temp = op - l.length(); // just value where to insert back
            l = Calculate(l, r, '/');
            if (l.compare(" ") == 0)
                return " ";
            exp.insert(temp, l);
        }
        op = exp.find('*');
        if (op != -1)
        {
            l = exp.substr(0, op); // split string to left and right of the operation
            r = exp.substr(op + 1, exp.length());
            exp.erase(op, 1); // remove that operation from the string
            leftOP = opFinder(l, false); // check if theres operation in those strings
            rightOP = opFinder(r, true);
            if (leftOP != -1) // if there is, get the number part only
                l = l.substr(leftOP + 1, l.length());
            if (rightOP != -1)
                r = r.substr(0, rightOP);
            exp.erase(op - l.length(), op + r.length()); // remove right and left number from the exp
            temp = op - l.length(); // just value where to insert back
            l = Calculate(l, r, '*');
            if (l.compare(" ") == 0)
                return " ";
            exp.insert(temp, l);
        }
        op = exp.find('+');
        if (op != -1)
        {
            l = exp.substr(0, op); // split string to left and right of the operation
            r = exp.substr(op + 1, exp.length());
            exp.erase(op, 1); // remove that operation from the string
            leftOP = opFinder(l, false); // check if theres operation in those strings
            rightOP = opFinder(r, true);
            if (leftOP != -1) // if there is, get the number part only
                l = l.substr(leftOP + 1, l.length());
            if (rightOP != -1)
                r = r.substr(0, rightOP);
            exp.erase(op - l.length(), op + r.length()); // remove right and left number from the exp
            temp = op - l.length(); // just value where to insert back
            l = Calculate(l, r, '+');
            if (l.compare(" ") == 0)
                return " ";
            exp.insert(temp, l);
        }
        op = exp.find('-');
        if (op != -1)
        {
            l = exp.substr(0, op); // split string to left and right of the operation
            r = exp.substr(op + 1, exp.length());
            exp.erase(op, 1); // remove that operation from the string
            leftOP = opFinder(l, false); // check if theres operation in those strings
            rightOP = opFinder(r, true);
            if (leftOP != -1) // if there is, get the number part only
                l = l.substr(leftOP + 1, l.length());
            if (rightOP != -1)
                r = r.substr(0, rightOP);
            exp.erase(op - l.length(), op + r.length()); // remove right and left number from the exp
            temp = op - l.length(); // just value where to insert back
            l = Calculate(l, r, '-');
            if (l.compare(" ") == 0)
                return " ";
            exp.insert(temp, l);
            
        }
        
    }
    return exp;
}

string Calculator(string input)
{
    string sum;
    int space = input.find(' ');
    while (space != -1) // simply remove " " from the string
    {
        input.erase(space, 1);
        space = input.find(' ');
    }
    int lp = input.find(')');
    while (lp != -1) // if theres ) in the string, deal with it
    {
        string temp = input.substr(0, lp);
        input.erase(lp, 1);
        int rp = temp.find_last_of('(');
        if (rp == -1)
        {
            cout << "\nCannot detect \"(\" accodringly";
            return " ";
        }
        temp = temp.substr(rp+1, temp.length());
        input.erase(rp, 1);
        input.erase(lp - temp.length() - 1, temp.length()); // delete everything in that ()
        sum = Evaluate(temp);
        if (sum.compare(" ") == 0)
            return " ";
        input.insert(lp - temp.length() - 1, sum);
        lp = input.find(')');
    }
    if (input.find('(') != -1)
    {
        cout << "\nThere is an extra \"(\" in the string";
        return " ";
    }
    input = Evaluate(input);
    if (input.compare(" ") == 0)
        return " ";
    return input;
}

int main()
{
    Convertor c;
    floatNum f;
    string input;
    float done;
    cout << "\nPlease enter an expression(enter q to quit) : ";
    std::getline(cin,input);
    while (input.compare("q") != 0)
    {
        input = Calculator(input);
        if (input.compare(" ") != 0)
        {
            f = c.FPLConvertor(input);
            cout << "\nThe result of this expression is " << f.num << endl;
        }
        cout << endl;
        cout << "Please enter an expression(enter q to quit) : ";
        std::getline(cin, input);
    }
    cout << "\nProgram termianted\n";
    system("pause");
    return 0;
}
