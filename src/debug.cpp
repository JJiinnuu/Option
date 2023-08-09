#include "debug.h"

#include <iostream>
#include <string>

#include <stdlib.h>

using namespace std;

void debug(int point) 
{
    cout << "[Debug]" << endl;
    cout << "Point: " << point << endl;
    cout << endl;
}

void debug(char c)
{
    cout << "[Debug]" << endl;
    cout << "Char: " << c << endl;
    cout << endl;
}

void debug(string str)
{
    cout << "[Debug]" << endl;
    cout << "String: " << str << endl;
    cout << endl;
}

void error(string name, string msg, int is_exit) 
{
    cout << "[Error]" << endl;
    cout << "Error Name: " << name << endl;
    cout << "Error Msg : " << msg  << endl;
    cout << endl;

    if (is_exit) exit(-1);
}