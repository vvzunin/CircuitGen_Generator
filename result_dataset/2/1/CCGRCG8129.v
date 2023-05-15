module CCGRCG8129(
	input x0, x1, x2, x3,
	output f1, f2, f3, f4, f5
);

	wire d1, d2, d3;

	and (d1, x2, x3);
	nor (d2, x0, x1);
	buf (d3, x0, x2);
	assign f1 = d1;
	assign f2 = d3;
	assign f3 = d1;
	assign f4 = d2;
	assign f5 = d1;
endmodule
