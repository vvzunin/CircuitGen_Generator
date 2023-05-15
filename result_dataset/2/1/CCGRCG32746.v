module CCGRCG32746(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	and (d1, x0, x2);
	nand (d2, x5);
	xor (d3, d1);
	buf (d4, d1);
	not (d5, x0);
	nand (d6, d3, d4);
	nand (d7, d3, d4);
	buf (d8, d4, d5);
	assign f1 = d8;
	assign f2 = d6;
	assign f3 = d8;
	assign f4 = d7;
	assign f5 = d7;
endmodule
