//f0 = (not x0 and x1)
//f1 = (x0 and not x1) or (x0 and x1)
//f2 = (not x0 and not x1) or (x0 and not x1)
//f3 = (not x0 and not x1)
//f4 = 1'b0
//f5 = (not x0 and x1)
module CCGRTT130_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	assign f0 = d1;
	and (d1, d2, x1);
	not (d2, x0);
	assign f1 = d3;
	or (d3, d4, d6);
	and (d4, x0, d5);
	not (d5, x1);
	and (d6, x0, x1);
	assign f2 = d7;
	or (d7, d4, d8);
	and (d8, d2, d5);
	assign f3 = d8;
	assign f4 = 1'b0;
	assign f5 = d1;
endmodule
