#ifndef __OPTION_H__
#define __OPTION_H__

#include <map>
#include <string>
#include <typeinfo>

using namespace std;

#define NONE string("none")
#define INT string("int")
#define STRING string("string")
#define INT_LIST string("int list")
#define STRING_LIST string("string list")

int export_int(string::const_iterator &it, const string::const_iterator end);
string export_string(string::const_iterator &it, const string::const_iterator end);

class Any {
    private:
        const string type_p;
        void *value_p;

        void set_value_int(string::const_iterator &it, const string::const_iterator end);
        void set_value_string(string::const_iterator &it, const string::const_iterator end);

        void set_value_int_list(string::const_iterator &it, const string::const_iterator end);
        void set_value_string_list(string::const_iterator &it, const string::const_iterator end);

    public:
        Any(const string type, const string value);
        ~Any(void);
        void set_value(const string value);
        string get_type(void);
        void print_type(void);
        void print_value(void);
};

class Option_Entry 
{
    private:
        const string name_p;
        const string description_p;

        Any value_p;

        int set_p;
        int necessary_p;

    public:
        Option_Entry(const string name, const string type, const string description,
                    const string value, const int neceessary);
        ~Option_Entry(void);
        void set_value(const string value);
        void check_necessary(void);
        void print_option_entry(void);
};

class Option 
{
    private: 
        map<string, Option_Entry *> option_list_p;

        void check_necessary(void);

    public:
        Option(void);
        ~Option(void);
        void add_option(const string name, const string type, const string description,
                        const string value, const int necessary);
        void parsing(int arg_num, char **args);
        void print_option(void);
};

#endif