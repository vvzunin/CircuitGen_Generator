module CCGRCG26843(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7;

	buf (d1, x1, x3);
	nand (d2, x1, x5);
	not (d3, x4);
	buf (d4, d1, d2);
	buf (d5, d3);
	and (d6, d3, d4);
	and (d7, d3, d4);
	assign f1 = d7;
	assign f2 = d6;
	assign f3 = d5;
	assign f4 = d5;
	assign f5 = d5;
endmodule
