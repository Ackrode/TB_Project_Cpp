#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
using namespace std;

string GetModule(string SVFilePath)
{
    ifstream f;
    f.open(SVFilePath, ios::in);
    stringstream SVCode;
    SVCode << f.rdbuf();
    f.close();
    string StrSVCode = SVCode.str();
    regex Pattern1("\\s*module\\s+(\\w+).*");
    smatch ModuleMatch;
    regex_search(StrSVCode, ModuleMatch, Pattern1);
    string Module = ModuleMatch.str(1);
    if (Module.empty())
    {
        Module = "-------";
        cout << "No module found" << endl;
    }
    return Module;
}