module CCGRCG5378(
	input x0, x1, x2,
	output f1, f2, f3, f4, f5, f6, f7, f8
);

	wire d1, d2, d3, d4, d5, d6;

	xnor (d1, x2);
	buf (d2, x0, x2);
	and (d3, x0);
	xnor (d4, x1, x2);
	nand (d5, d1, d3);
	buf (d6, d2, d3);
	assign f1 = d5;
	assign f2 = d6;
	assign f3 = d6;
	assign f4 = d5;
	assign f5 = d6;
	assign f6 = d6;
	assign f7 = d6;
	assign f8 = d6;
endmodule
