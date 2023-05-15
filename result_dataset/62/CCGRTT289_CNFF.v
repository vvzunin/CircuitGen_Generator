//f0 = (x0 or not x1) and (not x0 or not x1)
//f1 = (x0 or x1) and (x0 or not x1) and (not x0 or not x1)
//f2 = (x0 or x1)
//f3 = 1'b0
module CCGRTT289_CNFF(
	input x0, x1,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	not (d3, x1);
	or (d4, d3, d5);
	not (d5, x0);
	assign f1 = d6;
	and (d6, d1, d7);
	or (d7, x0, x1);
	assign f2 = d7;
	assign f3 = 1'b0;
endmodule
