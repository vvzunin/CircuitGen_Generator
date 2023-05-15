//f0 = (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2)
//f2 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT255_CNFF(
	input x0, x1, x2,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, d3, d4);
	not (d3, x0);
	or (d4, x1, d5);
	not (d5, x2);
	or (d6, d3, d7);
	or (d7, d5, d8);
	not (d8, x1);
	assign f1 = d9;
	and (d9, d10, d11);
	or (d10, x0, d4);
	and (d11, d12, d14);
	or (d12, x0, d13);
	or (d13, x2, d8);
	or (d14, x0, d7);
	assign f2 = d15;
	and (d15, d10, d16);
	and (d16, d12, d17);
	and (d17, d6, d18);
	or (d18, d3, d19);
	or (d19, x1, x2);
endmodule
