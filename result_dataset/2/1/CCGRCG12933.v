module CCGRCG12933(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7;

	or (d1, x2, x3);
	buf (d2, x0, x4);
	not (d3, x1);
	or (d4, d2, d3);
	not (d5, d3);
	nand (d6, d1, d3);
	or (d7, d1);
	assign f1 = d4;
	assign f2 = d7;
	assign f3 = d5;
endmodule
