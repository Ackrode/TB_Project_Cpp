`timescale 1ns/1ns
module AndGate_TB.sv;
reg [0:0] InA;
reg [0:0] InB;
reg [0:0] [1:0];
wire [0:0] OutY;
AndGate DUT(InA,InB,[1:0],OutY);
initial begin 
$dumpfile("design.vcd");
$dumpvars(0, AndGate_TB);
// addd stimulus
{InA, InB, [1:0] }=3'b0; #1
{InA, InB, [1:0] }=3'b1; #1
{InA, InB, [1:0] }=3'b10; #1
{InA, InB, [1:0] }=3'b11; #1
{InA, InB, [1:0] }=3'b100; #1
{InA, InB, [1:0] }=3'b101; #1
{InA, InB, [1:0] }=3'b110; #1
{InA, InB, [1:0] }=3'b111; #1
$finish;
end
endmodule
