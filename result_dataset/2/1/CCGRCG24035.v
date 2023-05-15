module CCGRCG24035(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	nand (d1, x5);
	or (d2, x0, x5);
	nor (d3, x1, x2);
	xnor (d4, d1);
	xor (d5, d2, d3);
	xnor (d6, d1, d2);
	not (d7, x4);
	buf (d8, d5);
	xor (d9, d6);
	assign f1 = d8;
	assign f2 = d9;
	assign f3 = d8;
endmodule
