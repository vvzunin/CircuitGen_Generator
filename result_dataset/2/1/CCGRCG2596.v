module CCGRCG2596(
	input x0, x1, x2,
	output f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6;

	xor (d1, x1, x2);
	buf (d2, x1, x2);
	xor (d3, x1, x2);
	nor (d4, d1);
	xor (d5, d1, d2);
	buf (d6, d2, d3);
	assign f1 = d6;
	assign f2 = d5;
	assign f3 = d4;
	assign f4 = d5;
	assign f5 = d6;
endmodule
