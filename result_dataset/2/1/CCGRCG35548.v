module CCGRCG35548(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3, f4, f5, f6, f7, f8
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	and (d1, x1, x2);
	xnor (d2, x0, x7);
	and (d3, x5, x6);
	xor (d4, x4, x7);
	nor (d5, d4);
	xor (d6, d3, d4);
	xor (d7, d2, d4);
	not (d8, x2);
	xor (d9, d7, d8);
	or (d10, d6, d7);
	assign f1 = d9;
	assign f2 = d9;
	assign f3 = d10;
	assign f4 = d10;
	assign f5 = d9;
	assign f6 = d9;
	assign f7 = d10;
	assign f8 = d9;
endmodule
