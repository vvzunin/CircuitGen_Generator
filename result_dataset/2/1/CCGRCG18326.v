module CCGRCG18326(
	input x0, x1, x2, x3, x4, x5,
	output f1, f2, f3
);

	wire d1, d2, d3, d4;

	and (d1, x1);
	or (d2, x0, x1);
	nand (d3, x0, x5);
	buf (d4, x0, x3);
	assign f1 = d4;
	assign f2 = d1;
	assign f3 = d2;
endmodule
