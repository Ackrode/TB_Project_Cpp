module AndGate(InA, InB, OutY);
  input InA;
  input InB;
  output OutY;
  
	assign OutY = InA & InB;	
endmodule