module CCGRCG12042(
	input x0, x1, x2, x3, x4,
	output f1, f2, f3
);

	wire d1, d2;

	xnor (d1, x3);
	not (d2, x1);
	assign f1 = d1;
	assign f2 = d1;
	assign f3 = d1;
endmodule
