module CCGRCG20180(
	input x0, x1, x2, x3, x4, x5,
	output f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	nand (d1, x1);
	buf (d2, x0, x1);
	nand (d3, x2, x4);
	and (d4, d1, d2);
	and (d5, d1, d2);
	nand (d6, d1, d3);
	not (d7, d3);
	xor (d8, d5);
	nor (d9, d5, d6);
	assign f1 = d7;
	assign f2 = d8;
	assign f3 = d8;
	assign f4 = d8;
	assign f5 = d8;
endmodule
