#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <string>

using namespace std;

void debug(int point);
void debug(char c);
void debug(string str);
void error(string name, string msg, int is_exit);

#endif