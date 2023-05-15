module CCGRCG22741(
	input x0, x1, x2, x3, x4, x5,
	output f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5;

	nor (d1, x3, x4);
	buf (d2, x3, x5);
	buf (d3, d2);
	xnor (d4, d1, d2);
	nor (d5, d2);
	assign f1 = d5;
	assign f2 = d5;
	assign f3 = d5;
	assign f4 = d3;
	assign f5 = d4;
	assign f6 = d4;
	assign f7 = d5;
endmodule
