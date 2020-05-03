#include <regex>
#include <string>
#include <iostream>
#include <exception>

using namespace std;
int main(int argc, char const *argv[])
{

    try
    {
        //regex reg("[[:alpha:]]*888[[:alpha:]]");
        regex reg("[[:alpha:]]*888[[:alpha:]]");
        string s = "hello shabi888ok";
        smatch ret;
        if (regex_search(s, ret, reg))
        {
            std::cout << "ret= " << ret.str() << std::endl;
        }
    }
    catch (const regex_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::regex r1("[[:anum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
    }
    catch (std::regex_error e)
    {
        std::cout << e.what() << "\ncode: " << e.code() << std::endl;
    }

    try
    {
        std::regex r1("[[:alnum:]+\\.(cpp|cxx|cc)$", std::regex::icase);
    }
    catch (std::regex_error e)
    {
        std::cout << e.what() << "\ncode: " << e.code() << std::endl;
    }

    try
    {
        std::regex r1("[[:alnum:]]+\\.cpp|cxx|cc)$", std::regex::icase);
    }
    catch (std::regex_error e)
    {
        std::cout << e.what() << "\ncode: " << e.code() << std::endl;
    }

    while (1)
        ;
    return 0;
}
