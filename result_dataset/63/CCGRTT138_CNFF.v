//f0 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
//f1 = (x0 or x1) and (x0 or not x1)
//f2 = (x0 or not x1) and (not x0 or not x1)
//f3 = (x0 or not x1) and (not x0 or x1) and (not x0 or not x1)
//f4 = 1'b0
//f5 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
module CCGRTT138_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	assign f0 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	and (d3, d4, d6);
	or (d4, x1, d5);
	not (d5, x0);
	or (d6, d5, d7);
	not (d7, x1);
	assign f1 = d8;
	and (d8, d2, d9);
	or (d9, x0, d7);
	assign f2 = d10;
	and (d10, d6, d9);
	assign f3 = d11;
	and (d11, d3, d9);
	assign f4 = 1'b0;
	assign f5 = d1;
endmodule
