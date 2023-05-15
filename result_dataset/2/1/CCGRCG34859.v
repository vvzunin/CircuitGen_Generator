module CCGRCG34859(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6;

	buf (d1, x0, x5);
	nand (d2, x5, x7);
	buf (d3, x0, x1);
	and (d4, d2, d3);
	or (d5, d2, d3);
	nor (d6, d1, d3);
	assign f1 = d4;
	assign f2 = d4;
	assign f3 = d6;
	assign f4 = d5;
	assign f5 = d4;
	assign f6 = d6;
	assign f7 = d4;
endmodule
