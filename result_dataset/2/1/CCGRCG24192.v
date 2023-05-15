module CCGRCG24192(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3
);

	wire d1, d2, d3, d4;

	nor (d1, x0);
	xnor (d2, x0, x6);
	and (d3, x4, x5);
	nand (d4, x0, x1);
	assign f1 = d2;
	assign f2 = d3;
	assign f3 = d4;
endmodule
