module CCGRCG31471(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3, f4
);

	wire d1, d2, d3;

	or (d1, x3, x7);
	xor (d2, x2, x4);
	xnor (d3, x1, x6);
	assign f1 = d2;
	assign f2 = d3;
	assign f3 = d1;
	assign f4 = d3;
endmodule
