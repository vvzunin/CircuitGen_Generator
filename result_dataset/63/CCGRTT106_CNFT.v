//f0 = 1'b0
//f1 = (not x0 and x1) or (x0 and not x1)
//f2 = (not x0 and not x1)
//f3 = (not x0 and not x1) or (x0 and not x1)
//f4 = (x0 and not x1) or (x0 and x1)
module CCGRTT106_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	assign f0 = 1'b0;
	assign f1 = d1;
	or (d1, d2, d4);
	and (d2, d3, x1);
	not (d3, x0);
	and (d4, x0, d5);
	not (d5, x1);
	assign f2 = d6;
	and (d6, d3, d5);
	assign f3 = d7;
	or (d7, d4, d6);
	assign f4 = d8;
	or (d8, d4, d9);
	and (d9, x0, x1);
endmodule
