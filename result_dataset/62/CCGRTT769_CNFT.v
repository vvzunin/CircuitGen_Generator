//f0 = (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2)
//f1 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2)
module CCGRTT769_CNFT(
	input x0, x1, x2,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	not (d5, x2);
	or (d6, d7, d9);
	and (d7, d3, d8);
	and (d8, x1, x2);
	and (d9, x0, d10);
	and (d10, d5, d11);
	not (d11, x1);
	assign f1 = d12;
	or (d12, d13, d14);
	and (d13, d3, d10);
	or (d14, d7, d15);
	or (d15, d9, d16);
	and (d16, x0, d17);
	and (d17, x2, d11);
endmodule
