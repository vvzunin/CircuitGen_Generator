//f0 = 1'b0
//f1 = (x0 or x1) and (x0 or not x1) and (not x0 or x1)
//f2 = (x0 or not x1) and (not x0 or x1) and (not x0 or not x1)
//f3 = (not x0 or not x1)
//f4 = 1'b0
//f5 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
//f6 = (not x0 or x1) and (not x0 or not x1)
//f7 = 1'b0
module CCGRTT209_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	assign f0 = 1'b0;
	assign f1 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	and (d3, d4, d6);
	or (d4, x0, d5);
	not (d5, x1);
	or (d6, x1, d7);
	not (d7, x0);
	assign f2 = d8;
	and (d8, d4, d9);
	and (d9, d6, d10);
	or (d10, d5, d7);
	assign f3 = d10;
	assign f4 = 1'b0;
	assign f5 = d11;
	and (d11, d2, d9);
	assign f6 = d9;
	assign f7 = 1'b0;
endmodule
