module CCGRCG28379(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3;

	and (d1, x2, x3);
	xor (d2, x1, x5);
	nor (d3, x0, x5);
	assign f1 = d1;
	assign f2 = d3;
	assign f3 = d1;
	assign f4 = d1;
	assign f5 = d1;
	assign f6 = d2;
	assign f7 = d2;
endmodule
