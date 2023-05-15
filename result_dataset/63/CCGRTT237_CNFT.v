//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and x1 and x2)
//f1 = (not x0 and not x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
module CCGRTT237_CNFT(
	input x0, x1, x2,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	or (d6, d7, d9);
	and (d7, d3, d8);
	and (d8, x1, x2);
	and (d9, x0, d8);
	assign f1 = d10;
	or (d10, d2, d11);
	or (d11, d12, d13);
	and (d12, x0, d4);
	and (d13, x0, d14);
	and (d14, x1, d15);
	not (d15, x2);
endmodule
