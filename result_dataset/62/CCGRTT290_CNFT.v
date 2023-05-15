//f0 = (not x0 and not x1) or (x0 and not x1)
//f1 = (x0 and not x1)
//f2 = (not x0 and x1) or (x0 and not x1) or (x0 and x1)
//f3 = 1'b0
module CCGRTT290_CNFT(
	input x0, x1,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	assign f0 = d1;
	or (d1, d2, d5);
	and (d2, d3, d4);
	not (d3, x0);
	not (d4, x1);
	and (d5, x0, d4);
	assign f1 = d5;
	assign f2 = d6;
	or (d6, d7, d8);
	and (d7, d3, x1);
	or (d8, d5, d9);
	and (d9, x0, x1);
	assign f3 = 1'b0;
endmodule
