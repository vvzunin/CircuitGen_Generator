module CCGRCG9519(
	input x0, x1, x2, x3,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6;

	xnor (d1, x1, x3);
	buf (d2, x0, x3);
	nand (d3, x0, x2);
	not (d4, x1);
	nand (d5, d3);
	or (d6, d1);
	assign f1 = d5;
	assign f2 = d6;
	assign f3 = d6;
	assign f4 = d4;
	assign f5 = d4;
	assign f6 = d4;
endmodule
