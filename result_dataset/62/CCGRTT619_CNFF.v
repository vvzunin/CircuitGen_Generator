//f0 = (x0 or x1)
//f1 = 1'b1
//f2 = (x0 or x1) and (x0 or not x1) and (not x0 or x1)
//f3 = (x0 or x1)
//f4 = (x0 or not x1)
//f5 = (x0 or x1) and (x0 or not x1)
//f6 = (x0 or not x1) and (not x0 or x1)
//f7 = (x0 or not x1) and (not x0 or x1) and (not x0 or not x1)
module CCGRTT619_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	assign f0 = d1;
	or (d1, x0, x1);
	assign f1 = 1'b1;
	assign f2 = d2;
	and (d2, d1, d3);
	and (d3, d4, d6);
	or (d4, x0, d5);
	not (d5, x1);
	or (d6, x1, d7);
	not (d7, x0);
	assign f3 = d1;
	assign f4 = d4;
	assign f5 = d8;
	and (d8, d1, d4);
	assign f6 = d3;
	assign f7 = d9;
	and (d9, d4, d10);
	and (d10, d6, d11);
	or (d11, d5, d7);
endmodule
