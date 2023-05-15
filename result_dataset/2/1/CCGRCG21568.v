module CCGRCG21568(
	input x0, x1, x2, x3, x4, x5,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4;

	or (d1, x0, x5);
	xnor (d2, x1, x4);
	or (d3, x0, x3);
	buf (d4, x0, x1);
	assign f1 = d1;
	assign f2 = d4;
	assign f3 = d1;
	assign f4 = d1;
	assign f5 = d3;
	assign f6 = d3;
endmodule
