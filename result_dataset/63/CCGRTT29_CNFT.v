//f0 = (not x0 and x1) or (x0 and x1)
//f1 = (not x0 and x1)
module CCGRTT29_CNFT(
	input x0, x1,
	output f0, f1
);

	wire d1, d2, d3, d4;

	assign f0 = d1;
	or (d1, d2, d4);
	and (d2, d3, x1);
	not (d3, x0);
	and (d4, x0, x1);
	assign f1 = d2;
endmodule
