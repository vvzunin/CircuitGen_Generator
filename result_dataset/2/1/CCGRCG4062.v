module CCGRCG4062(
	input x0, x1, x2,
	output f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3;

	nor (d1, x0, x2);
	nand (d2, x1, x2);
	xnor (d3, x0, x2);
	assign f1 = d3;
	assign f2 = d2;
	assign f3 = d1;
	assign f4 = d2;
	assign f5 = d3;
	assign f6 = d1;
	assign f7 = d3;
endmodule
