//f0 = (x0 or x1) and (x0 or not x1) and (not x0 or x1)
//f1 = (not x0 or not x1)
//f2 = (x0 or x1) and (not x0 or not x1)
//f3 = (not x0 or x1)
module CCGRTT237_CNFF(
	input x0, x1,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	assign f0 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	and (d3, d4, d6);
	or (d4, x0, d5);
	not (d5, x1);
	or (d6, x1, d7);
	not (d7, x0);
	assign f1 = d8;
	or (d8, d5, d7);
	assign f2 = d9;
	and (d9, d2, d8);
	assign f3 = d6;
endmodule
