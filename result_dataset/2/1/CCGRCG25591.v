module CCGRCG25591(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7;

	nand (d1, x3, x5);
	nand (d2, x0);
	nor (d3, x3, x5);
	or (d4, x0, x4);
	buf (d5, d1, d3);
	and (d6, d3, d4);
	xnor (d7, d3, d4);
	assign f1 = d7;
	assign f2 = d6;
	assign f3 = d5;
	assign f4 = d5;
endmodule
