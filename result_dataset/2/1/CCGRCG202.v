module CCGRCG202(
	input x0, x1, x2,
	output f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6;

	not (d1, x2);
	and (d2, x0, x1);
	nor (d3, d1, d2);
	xnor (d4, d1, d2);
	not (d5, x1);
	or (d6, d3, d4);
	assign f1 = d6;
	assign f2 = d5;
	assign f3 = d6;
endmodule
