module CCGRCG28895(
	input x0, x1, x2, x3, x4, x5, x6,
	output f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	nand (d1, x1, x6);
	nand (d2, x1);
	or (d3, x2, x6);
	nor (d4, x4);
	and (d5, d1, d2);
	buf (d6, d3);
	not (d7, x4);
	not (d8, x0);
	assign f1 = d6;
	assign f2 = d5;
	assign f3 = d6;
	assign f4 = d5;
	assign f5 = d5;
	assign f6 = d5;
	assign f7 = d7;
endmodule
