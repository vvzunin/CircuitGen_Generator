module CCGRCG3061(
	input x0, x1, x2,
	output f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	not (d1, x1);
	buf (d2, x1, x2);
	or (d3, d1, d2);
	not (d4, d2);
	nor (d5, d2);
	and (d6, d3, d4);
	nor (d7, d3, d5);
	nor (d8, d3, d5);
	buf (d9, d4, d5);
	assign f1 = d9;
	assign f2 = d6;
	assign f3 = d9;
	assign f4 = d7;
	assign f5 = d7;
	assign f6 = d8;
endmodule
