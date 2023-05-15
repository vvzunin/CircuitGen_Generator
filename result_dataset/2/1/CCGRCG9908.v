module CCGRCG9908(
	input x0, x1, x2, x3,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12;

	nor (d1, x1, x3);
	or (d2, x0);
	xor (d3, x1, x2);
	xnor (d4, x0, x1);
	nor (d5, d3);
	or (d6, d1, d4);
	buf (d7, d4);
	xor (d8, d1, d4);
	or (d9, d6, d8);
	xor (d10, d7, d8);
	nand (d11, d5, d6);
	buf (d12, d5, d6);
	assign f1 = d9;
	assign f2 = d12;
	assign f3 = d9;
	assign f4 = d9;
	assign f5 = d12;
	assign f6 = d11;
endmodule
