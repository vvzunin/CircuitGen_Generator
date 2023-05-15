module CCGRCG545(
	input x0, x1, x2,
	output f1, f2, f3
);

	wire d1, d2, d3;

	xnor (d1, x0, x2);
	nand (d2, x1);
	nor (d3, x1, x2);
	assign f1 = d1;
	assign f2 = d2;
	assign f3 = d1;
endmodule
