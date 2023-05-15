//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2)
//f1 = (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2)
module CCGRTT241_CNFT(
	input x0, x1, x2,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	and (d6, d3, d7);
	and (d7, x1, d8);
	not (d8, x2);
	assign f1 = d9;
	or (d9, d10, d12);
	and (d10, x0, d11);
	and (d11, d5, d8);
	and (d12, x0, d7);
	assign f2 = d13;
	or (d13, d14, d15);
	and (d14, d3, d11);
	or (d15, d10, d16);
	and (d16, d3, d17);
	and (d17, x1, x2);
endmodule
