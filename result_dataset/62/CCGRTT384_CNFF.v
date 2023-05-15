//f0 = (x0 or not x1) and (not x0 or not x1)
//f1 = (x0 or x1) and (not x0 or x1)
//f2 = 1'b0
//f3 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
//f4 = (x0 or x1)
module CCGRTT384_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	not (d3, x1);
	or (d4, d3, d5);
	not (d5, x0);
	assign f1 = d6;
	and (d6, d7, d8);
	or (d7, x0, x1);
	or (d8, x1, d5);
	assign f2 = 1'b0;
	assign f3 = d9;
	and (d9, d7, d10);
	and (d10, d4, d8);
	assign f4 = d7;
endmodule
