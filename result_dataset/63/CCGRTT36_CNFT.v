//f0 = (not x0 and x1) or (x0 and not x1)
//f1 = 1'b0
//f2 = (not x0 and not x1) or (x0 and x1)
module CCGRTT36_CNFT(
	input x0, x1,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	assign f0 = d1;
	or (d1, d2, d4);
	and (d2, d3, x1);
	not (d3, x0);
	and (d4, x0, d5);
	not (d5, x1);
	assign f1 = 1'b0;
	assign f2 = d6;
	or (d6, d7, d8);
	and (d7, d3, d5);
	and (d8, x0, x1);
endmodule
