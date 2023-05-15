module CCGRCG15525(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7;

	not (d1, x4);
	not (d2, x2);
	xor (d3, x1, x2);
	buf (d4, d3);
	and (d5, d1, d3);
	buf (d6, d1, d2);
	buf (d7, d2);
	assign f1 = d5;
	assign f2 = d4;
	assign f3 = d7;
	assign f4 = d7;
	assign f5 = d7;
	assign f6 = d5;
endmodule
