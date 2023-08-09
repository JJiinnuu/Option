#include "option.h"
#include "debug.h"

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <typeinfo>

#include <ctype.h>

using namespace std;

Option::Option(void)
{

}

Option::~Option(void)
{
    map<string, Option_Entry *>::iterator it;
    
    for (it = option_list_p.begin(); it != option_list_p.end(); it++)
        delete it->second;
}

void Option::add_option(const string name, const string type, const string description,
                        const string value, const int necessary)
{
    if (option_list_p.find(name) == option_list_p.end()) 
    {
        option_list_p[name] = new Option_Entry(name, type, description, value, necessary);
        return;
    }

    int is_exit = 1;
    string error_name = string("Option Name Collision");
    string error_msg;

    error_msg += string("The option name \"");
    error_msg += name;
    error_msg += string("\" is already exist.");

    error(error_name, error_msg, is_exit);
}

void Option::parsing(int arg_num, char **args) 
{
    int arg_index = 0;

    while (arg_index != arg_num)
    {
        map<string, Option_Entry *>::iterator option_entry;
        option_entry = option_list_p.find(string(args[arg_index]));

        if (option_entry == option_list_p.end())
        {
            int is_exit = 1;
            string error_name = string("Option Name Invaild");
            string error_msg;

            error_msg += string("The option name \"");
            error_msg += string(args[arg_index]);
            error_msg += string("\" is not exist.");

            error(error_name, error_msg, is_exit);
        }

        arg_index++;

        string value;
        while(option_list_p.find(string(args[arg_index])) == option_list_p.end())
        {
            value += string(" ");
            value += string(args[arg_index]);

            arg_index++;

            if (arg_index == arg_num) break;
        }

        option_entry->second->set_value(value);
    }

    this->check_necessary();
}

void Option::check_necessary(void)
{
    map<string, Option_Entry *>::iterator it;

    for (it = option_list_p.begin(); it != option_list_p.end(); it++)
        it->second->check_necessary();
}

void Option::print_option(void)
{
    map<string, Option_Entry *>::iterator it;

    for (it = option_list_p.begin(); it != option_list_p.end(); it++)
        it->second->print_option_entry();
}

Option_Entry::Option_Entry(const string name, const string type, const string description,
                           const string value, int necessary) :
name_p(name), description_p(description), value_p(type, value), necessary_p(necessary)
{

}

Option_Entry::~Option_Entry(void)
{

}

void Option_Entry::set_value(const string value)
{
    value_p.set_value(value);
    set_p = 1;
}

void Option_Entry::check_necessary(void)
{
    if (necessary_p && (!set_p))
    {
        int is_exit = 1;
        string error_name = string("Option Unsetting");
        string error_msg;

        error_msg += string("The option \"");
        error_msg += name_p;
        error_msg += string("\" is not setting.");

        error(error_name, error_msg, is_exit);
    }
}

void Option_Entry::print_option_entry(void)
{
    cout << "[" << name_p << "]" << endl;
    cout << "Description: " << description_p << endl;

    cout << "Type:        ";
    value_p.print_type();

    cout << "Value:       ";
    value_p.print_value();

    cout << "Necessary:   " << necessary_p << endl;
    cout << endl;
}

Any::Any(const string type, const string value) :
type_p(type)
{
    if (type_p == NONE) value_p = NULL;
    else if (type_p == INT) value_p = new int;
    else if (type_p == STRING) value_p = new string;
    else if (type_p == INT_LIST) value_p = new list<int>;
    else if (type_p == STRING_LIST) value_p = new list<string>;
    else 
    {
        int is_exit = 1;
        string error_name = string("Option Type Invaild");
        string error_msg;

        error_msg += string("The Any type of  \"");
        error_msg += type_p;
        error_msg += string("\" is invaild exist.");

        error(error_name, error_msg, is_exit);

        return;
    }

    this->set_value(value);
}

Any::~Any(void)
{
    if (type_p == INT) delete (int *)value_p;
    else if (type_p == STRING) delete (string *)value_p;
    else if (type_p == INT_LIST) delete (list<int> *)value_p;
    else if (type_p == STRING_LIST) delete (list<string> *)value_p;
}

void Any::set_value(const string value)
{   
    string::const_iterator it = value.begin();
    string::const_iterator end = value.end();

    if (type_p == INT) this->set_value_int(it, end);
    else if (type_p == STRING) this->set_value_string(it, end);
    else if (type_p == INT_LIST) this->set_value_int_list(it, end);
    else if (type_p == STRING_LIST) this->set_value_string_list(it, end);

    if (it == end) return;

    int is_exit = 1;
    string error_name = string("Too Many Option Value");;
    string error_msg;

    error_msg += string("Given value of option \"");
    error_msg += value;
    error_msg += string("\" is too many.");

    error(error_name, error_msg, is_exit);
}

void Any::set_value_int(string::const_iterator &it, const string::const_iterator end)
{
    *(int *)value_p = export_int(it, end);
}

void Any::set_value_string(string::const_iterator &it, const string::const_iterator end)
{
    *(string *)value_p = export_string(it, end);
}

void Any::set_value_int_list(string::const_iterator &it, const string::const_iterator end)
{   
    (*(list<int> *)value_p).clear();
    while (it != end)
        (*(list<int> *)value_p).push_back(export_int(it, end));
}

void Any::set_value_string_list(string::const_iterator &it, const string::const_iterator end)
{   
    (*(list<string> *)value_p).clear();
    while (it != end)
        (*(list<string> *)value_p).push_back(export_string(it, end));
}

string Any::get_type(void)
{
    return type_p;
}

void Any::print_type(void)
{
    cout << type_p << endl;
}

void Any::print_value(void)
{
    if (type_p == INT) cout << *(int *)value_p << endl;
    else if (type_p == STRING) cout << *(string *)value_p << endl;
    else if (type_p == INT_LIST)
    {
        list<int>::iterator it;
        list<int> *value = (list<int> *)value_p;

        for (it = value->begin(); it != value->end(); it++)
            cout << *it << ", ";
        cout << endl;
    }
    else if (type_p == STRING_LIST)
    {
        list<string>::iterator it;
        list<string> *value = (list<string> *)value_p;

        for (it = value->begin(); it != value->end(); it++)
            cout << *it << ", ";
        cout << endl;
    }
}

int export_int(string::const_iterator &it, const string::const_iterator end)
{
    int start = 0;
    int success = 1;
    string value = string("0");

    while (it != end)
    {
        if (isalpha(*it)) {
            success = 0;
            break;
        }
        else if (( start) && (!isdigit(*it))) break;
        else if ((!start) && ( isdigit(*it))) start = 1;

        if (start) value += *it;

        it++;
    }

    if (success) return stoi(value);
    
    int is_exit = 1;
    string error_name = string("Export Value Fail");;
    string error_msg;

    error_msg += string("Export int value from \"");
    error_msg += value + *it;
    error_msg += string("\" is fail.");

    error(error_name, error_msg, is_exit);

    return 0;
}

string export_string(string::const_iterator &it, const string::const_iterator end)
{
    int start = 0;
    string value;

    while (it != end)
    {
        if ((start) && (isspace(*it))) break;
        else if ((!start) && (!isspace(*it))) start = 1;

        if (start) value += *it;

        it++;
    }

    return value;
}