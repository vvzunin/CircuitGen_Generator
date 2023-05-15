module CCGRCG19228(
	input x0, x1, x2, x3, x4, x5,
	output f1, f2, f3, f4
);

	wire d1, d2, d3;

	not (d1, x5);
	or (d2, x1);
	xnor (d3, d1);
	assign f1 = d3;
	assign f2 = d3;
	assign f3 = d3;
	assign f4 = d3;
endmodule
