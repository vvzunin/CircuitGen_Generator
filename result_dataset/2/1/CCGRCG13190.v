module CCGRCG13190(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	nor (d1, x4);
	buf (d2, x0, x2);
	and (d3, x1, x4);
	not (d4, x1);
	xnor (d5, d2, d3);
	nor (d6, d2, d3);
	not (d7, d5);
	buf (d8, d5);
	or (d9, d5, d6);
	assign f1 = d7;
	assign f2 = d9;
	assign f3 = d9;
	assign f4 = d7;
endmodule
