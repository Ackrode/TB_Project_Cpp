#include <fstream>
#include <string>
#include <map>
#include <array>
#include "stimuls.h"
using namespace std;
// get number of input bits
int get_n(map <string,array<int,2>> inputs){
    int n=0;
    //iterate trough all inputs
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        n+=it->second[1]-it->second[0]+1;
    }
    return n;
}

void backbone(map <string,array<int,2>> inputs,map <string,array<int,2>>  outputs, string module)
{
    string testbench;
  // used in the same order as described above:
    testbench.append("`timescale 1ns/1ns\n");                       
    testbench.append("module "+ module +"_TB.sv;\n");   
    ofstream outfile;
    //iterate through the map and write the inputs with their bus size
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        testbench.append("reg ["+to_string(it->second[0])+":"+to_string(it->second[1])+"] " +it->first+ ";\n");
    }
    for (auto it = outputs.begin(); it != outputs.end(); ++it)
    {
        testbench.append("wire ["+to_string(it->second[0])+":"+to_string(it->second[1])+"] " +it->first+ ";\n");
    }
    testbench.append(module +" DUT(");
    // Append the DUT unit with all the inputs and outputs
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        testbench.append(it->first+",");
    }
    for (auto it = outputs.begin(); it != outputs.end(); ++it)
    {
        testbench.append(it->first+",");
    }
    //remove the last comma
    testbench.erase(testbench.end()-1);
    testbench.append(");\n");
    testbench.append("initial begin \n");
    testbench.append("$dumpfile(\"design.vcd\");\n");
    testbench.append("$dumpvars(0, "+ module +"_TB);\n");
    testbench.append("// addd stimulus\n");
    int n=get_n(inputs);
    testbench.append(stimulus(n,inputs));
    testbench.append("$finish;\n");
    testbench.append("end\n");
    testbench.append("endmodule\n");
    // Write files with the testbench
    outfile.open ( module + "_TB.sv");
    outfile << testbench;
}
