module CCGRCG6608(
	input x0, x1, x2, x3,
	output f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7;

	not (d1, x3);
	buf (d2, x1);
	xnor (d3, d1, d2);
	nor (d4, d1);
	buf (d5, d1, d2);
	buf (d6, d4, d5);
	nand (d7, d4);
	assign f1 = d6;
	assign f2 = d7;
	assign f3 = d6;
endmodule
