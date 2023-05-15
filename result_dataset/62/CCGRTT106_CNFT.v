//f0 = (not x0 and x1) or (x0 and not x1) or (x0 and x1)
//f1 = (not x0 and not x1) or (x0 and not x1) or (x0 and x1)
//f2 = (not x0 and x1)
module CCGRTT106_CNFT(
	input x0, x1,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	assign f0 = d1;
	or (d1, d2, d4);
	and (d2, d3, x1);
	not (d3, x0);
	or (d4, d5, d7);
	and (d5, x0, d6);
	not (d6, x1);
	and (d7, x0, x1);
	assign f1 = d8;
	or (d8, d4, d9);
	and (d9, d3, d6);
	assign f2 = d2;
endmodule
