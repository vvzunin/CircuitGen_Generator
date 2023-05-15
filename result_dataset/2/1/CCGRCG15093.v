module CCGRCG15093(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2;

	nor (d1, x1, x3);
	not (d2, x3);
	assign f1 = d1;
	assign f2 = d2;
	assign f3 = d1;
	assign f4 = d1;
	assign f5 = d1;
	assign f6 = d1;
endmodule
