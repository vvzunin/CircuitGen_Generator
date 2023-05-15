module CCGRCG33482(
	input x0, x1, x2, x3, x4, x5, x6, x7,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2;

	nor (d1, x3, x6);
	and (d2, x0, x2);
	assign f1 = d2;
	assign f2 = d2;
	assign f3 = d2;
	assign f4 = d2;
	assign f5 = d2;
	assign f6 = d2;
endmodule
