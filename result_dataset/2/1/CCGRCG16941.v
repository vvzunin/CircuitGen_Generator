module CCGRCG16941(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	nand (d1, x1, x3);
	or (d2, x0, x3);
	buf (d3, x0, x1);
	nand (d4, x0, x2);
	buf (d5, d1);
	or (d6, d1, d2);
	nor (d7, d1, d3);
	and (d8, d5, d6);
	and (d9, d6, d7);
	and (d10, d6, d7);
	nor (d11, d6, d7);
	assign f1 = d8;
	assign f2 = d9;
	assign f3 = d8;
	assign f4 = d11;
	assign f5 = d9;
	assign f6 = d11;
	assign f7 = d9;
endmodule
