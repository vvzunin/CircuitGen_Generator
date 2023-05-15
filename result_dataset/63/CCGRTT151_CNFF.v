//f0 = (x0 or x1) and (x0 or not x1) and (not x0 or not x1)
//f1 = 1'b0
//f2 = (x0 or not x1) and (not x0 or x1) and (not x0 or not x1)
//f3 = (x0 or not x1) and (not x0 or x1) and (not x0 or not x1)
//f4 = (x0 or x1) and (not x0 or x1)
//f5 = (x0 or x1) and (x0 or not x1) and (not x0 or not x1)
//f6 = (not x0 or x1) and (not x0 or not x1)
module CCGRTT151_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	assign f0 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	and (d3, d4, d6);
	or (d4, x0, d5);
	not (d5, x1);
	or (d6, d5, d7);
	not (d7, x0);
	assign f1 = 1'b0;
	assign f2 = d8;
	and (d8, d4, d9);
	and (d9, d6, d10);
	or (d10, x1, d7);
	assign f3 = d8;
	assign f4 = d11;
	and (d11, d2, d10);
	assign f5 = d1;
	assign f6 = d9;
endmodule
