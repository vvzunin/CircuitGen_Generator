//f0 = (x0 and not x1)
//f1 = 1'b0
//f2 = (not x0 and not x1)
//f3 = (not x0 and not x1)
//f4 = (not x0 and x1) or (x0 and x1)
//f5 = (x0 and not x1)
//f6 = (not x0 and not x1) or (not x0 and x1)
module CCGRTT153_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	assign f0 = d1;
	and (d1, x0, d2);
	not (d2, x1);
	assign f1 = 1'b0;
	assign f2 = d3;
	and (d3, d2, d4);
	not (d4, x0);
	assign f3 = d3;
	assign f4 = d5;
	or (d5, d6, d7);
	and (d6, x1, d4);
	and (d7, x0, x1);
	assign f5 = d1;
	assign f6 = d8;
	or (d8, d3, d6);
endmodule
