module CCGRCG11646(
	input x0, x1, x2, x3,
	output f1, f2, f3, f4, f5, f6, f7, f8
);

	wire d1, d2;

	xnor (d1, x2);
	not (d2, x1);
	assign f1 = d1;
	assign f2 = d1;
	assign f3 = d1;
	assign f4 = d2;
	assign f5 = d2;
	assign f6 = d1;
	assign f7 = d1;
	assign f8 = d2;
endmodule
