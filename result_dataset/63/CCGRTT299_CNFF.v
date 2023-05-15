//f0 = (x0 or x1 or not x2) and (x0 or not x1 or x2)
//f1 = (x0 or x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2)
module CCGRTT299_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	or (d5, x0, d6);
	or (d6, x2, d7);
	not (d7, x1);
	assign f1 = d8;
	and (d8, d2, d9);
	and (d9, d10, d12);
	or (d10, d3, d11);
	not (d11, x0);
	or (d12, d11, d13);
	or (d13, d4, d7);
	assign f2 = d14;
	and (d14, d5, d15);
	and (d15, d12, d16);
	or (d16, x0, d13);
	assign f3 = d17;
	and (d17, d2, d18);
	and (d18, d10, d16);
endmodule
