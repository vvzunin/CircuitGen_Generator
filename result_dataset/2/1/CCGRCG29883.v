module CCGRCG29883(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3, f4, f5, f6, f7, f8
);

	wire d1, d2, d3, d4, d5, d6;

	buf (d1, x2, x5);
	xnor (d2, x2, x5);
	xnor (d3, d1, d2);
	nand (d4, d1, d2);
	or (d5, d4);
	xnor (d6, d4);
	assign f1 = d5;
	assign f2 = d5;
	assign f3 = d5;
	assign f4 = d6;
	assign f5 = d6;
	assign f6 = d6;
	assign f7 = d5;
	assign f8 = d5;
endmodule
