#include "option.h"

#include <string>
#include <typeinfo>

using namespace std;

int main(int argc, char **argv) 
{
    if (argc == 1) return -1;

    Option option = Option();

    option.add_option("--script", "string", "The script file of vector generator.", 
                      "./vecotr_sciprt", 1);
                      
    option.parsing(argc-1, argv+1);

    option.print_option();
}