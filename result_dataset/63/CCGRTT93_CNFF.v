//f0 = 1'b0
//f1 = (x0 or x1) and (not x0 or not x1)
//f2 = (x0 or not x1) and (not x0 or x1) and (not x0 or not x1)
//f3 = (x0 or not x1) and (not x0 or not x1)
//f4 = (x0 or x1) and (x0 or not x1)
module CCGRTT93_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	assign f0 = 1'b0;
	assign f1 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	or (d3, d4, d5);
	not (d4, x0);
	not (d5, x1);
	assign f2 = d6;
	and (d6, d7, d8);
	or (d7, x0, d5);
	and (d8, d3, d9);
	or (d9, x1, d4);
	assign f3 = d10;
	and (d10, d3, d7);
	assign f4 = d11;
	and (d11, d2, d7);
endmodule
