module CCGRCG31721(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6;

	buf (d1, x0, x6);
	nand (d2, x2, x3);
	xor (d3, x0, x6);
	nand (d4, x3, x6);
	xnor (d5, d1, d4);
	nand (d6, d1, d3);
	assign f1 = d6;
	assign f2 = d6;
	assign f3 = d6;
	assign f4 = d5;
endmodule
