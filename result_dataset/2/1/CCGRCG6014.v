module CCGRCG6014(
	input x0, x1, x2, x3,
	output f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6;

	xnor (d1, x1, x2);
	buf (d2, x1, x3);
	and (d3, x0, x1);
	xnor (d4, x1, x2);
	nand (d5, d1, d3);
	buf (d6, d2, d3);
	assign f1 = d5;
	assign f2 = d6;
	assign f3 = d6;
endmodule
