
#include "backbone.h"
#include "get_inouts.h"
#include "module.h"
//using namespace std;

int main()
{
    string file_name = "prueba.sv";
    string module;
    map <string,array<int,2>> inputs;
    map <string,array<int,2>> outputs;
    array<map<string, array<int,2>>,2> inouts;
    inouts = get_inouts(file_name);
    module=GetModule(file_name);
    backbone(inouts[0],inouts[1],module);

}