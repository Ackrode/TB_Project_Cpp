`timescale 1ns/1ns
module AndGate_TB.v;
reg [0:0] InA;
reg [0:0] InB;
wire [0:0] InA;
AndGate DUT(InA,InB,InA);
initial begin 
$dumpfile("design.vcd");
$dumpvars(0, AndGate_TB);
// addd stimulus
{InA, InB }=2'b0; #1
{InA, InB }=2'b1; #1
{InA, InB }=2'b10; #1
{InA, InB }=2'b11; #1
$finish;
end
endmodule