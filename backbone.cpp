#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <array>
using namespace std;
    /*`timescale 1ns/1ns
    module module+"_TB.v";
    reg inputs;
    wire outputs;
    module DUT(inputs, outputs);
    initial begin 
        $dumpfile("design.vcd");
        $dumpvars(0, module+"_TB);
        // addd stimulus

        $finish;
    end
    endmodule*/
int main ()
{
    string testbench;
    string module="aaaa";
    map <string,array<int,2>> inputs;
    inputs.insert(pair<string,array <int, 2>>("a",{2,0}));
    inputs.insert(pair<string,array <int, 2>>("b",{2,0}));
    map <string,array<int,2>>  outputs;
    outputs.insert(pair<string,array <int, 2>>("c",{1,0}));
    outputs.insert(pair<string,array <int, 2>>("d",{2,0}));
    ofstream outfile("module_TB.sv");
  // used in the same order as described above:
    testbench.append("`timescale 1ns/1ns\n");                       
    testbench.append("module "+ module +"_TB.v;\n");   

    //iterate through the map
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
    {
        testbench.append("reg ["+to_string(it->second[0])+":"+to_string(it->second[1])+"] " +it->first+ ";\n");
    }
    for (auto it = outputs.begin(); it != outputs.end(); ++it)
    {
        testbench.append("wire ["+to_string(it->second[0])+":"+to_string(it->second[1])+"] " +it->first+ ";\n");
    }
    testbench.append(module +" DUT(");
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
    testbench.append("$finish;\n");
    testbench.append("end\n");
    testbench.append("endmodule\n");

    outfile << testbench;
  return 0;
}
