module CCGRCG30261(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6;

	buf (d1, x2, x7);
	xnor (d2, x2, x3);
	xnor (d3, d1, d2);
	nand (d4, d1, d2);
	or (d5, d4);
	xnor (d6, d4);
	assign f1 = d5;
	assign f2 = d5;
	assign f3 = d5;
endmodule
