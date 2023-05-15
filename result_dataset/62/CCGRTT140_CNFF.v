//f0 = (x0 or x1)
//f1 = (x0 or not x1)
//f2 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
module CCGRTT140_CNFF(
	input x0, x1,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	assign f0 = d1;
	or (d1, x0, x1);
	assign f1 = d2;
	or (d2, x0, d3);
	not (d3, x1);
	assign f2 = d4;
	and (d4, d1, d5);
	and (d5, d6, d8);
	or (d6, x1, d7);
	not (d7, x0);
	or (d8, d3, d7);
endmodule
