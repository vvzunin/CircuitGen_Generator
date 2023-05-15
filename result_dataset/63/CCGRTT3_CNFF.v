//f0 = (x0 or x1) and (not x0 or x1)
//f1 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
module CCGRTT3_CNFF(
	input x0, x1,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	assign f0 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	or (d3, x1, d4);
	not (d4, x0);
	assign f1 = d5;
	and (d5, d2, d6);
	and (d6, d3, d7);
	or (d7, d4, d8);
	not (d8, x1);
endmodule
