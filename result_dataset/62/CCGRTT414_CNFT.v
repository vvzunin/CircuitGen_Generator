//f0 = (not x0 and not x1) or (not x0 and x1)
//f1 = (x0 and x1)
//f2 = (not x0 and x1) or (x0 and not x1) or (x0 and x1)
//f3 = (not x0 and x1) or (x0 and x1)
//f4 = (not x0 and x1) or (x0 and not x1) or (x0 and x1)
//f5 = 1'b0
module CCGRTT414_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	assign f0 = d1;
	or (d1, d2, d5);
	and (d2, d3, d4);
	not (d3, x0);
	not (d4, x1);
	and (d5, d3, x1);
	assign f1 = d6;
	and (d6, x0, x1);
	assign f2 = d7;
	or (d7, d5, d8);
	or (d8, d6, d9);
	and (d9, x0, d4);
	assign f3 = d10;
	or (d10, d5, d6);
	assign f4 = d7;
	assign f5 = 1'b0;
endmodule
