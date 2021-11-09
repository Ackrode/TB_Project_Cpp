#include <iostream>
#include <regex>
#include <string>
 using namespace std;
int main()
{
    string target("module andgate(uno, dos, tres);");
    smatch sm;
 
    regex re1("^\\s*module\\s+(\\w+)");
    regex_search(target, sm, re1);
     cout << "entire match: " << sm.str(0) << '\n'
              << "submatch #1: " << sm.str(1) << '\n'
              << "subffix " << sm.suffix() <<endl;

    string target2 = sm.suffix();
    regex re2("(\\w+)+");
    regex_search(target2, sm, re2);
     
     cout << "entire match: " << sm.str(0) << '\n'
              << "submatch #1: " << sm.str(1) << '\n'
              << "suffix : " << sm.suffix() << '\n' ;

    string target3=sm.suffix();
    regex_search(target3, sm, re2);
    cout << "entire match: " << sm.str(0) << '\n'
             << "submatch #1: " << sm.str(1) << '\n'
            << "suffix : " << sm.suffix() << '\n' ;
 
}