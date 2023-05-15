module CCGRCG17574(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3, f4, f5, f6, f7, f8
);

	wire d1, d2, d3, d4;

	and (d1, x0, x2);
	or (d2, x0, x4);
	nand (d3, x0, x2);
	buf (d4, x0, x1);
	assign f1 = d4;
	assign f2 = d1;
	assign f3 = d2;
	assign f4 = d2;
	assign f5 = d2;
	assign f6 = d2;
	assign f7 = d4;
	assign f8 = d4;
endmodule
