//f0 = (not x0 and not x1) or (x0 and not x1) or (x0 and x1)
//f1 = (not x0 and x1) or (x0 and x1)
//f2 = (not x0 and x1) or (x0 and not x1)
//f3 = (not x0 and x1)
//f4 = 1'b0
//f5 = (x0 and not x1) or (x0 and x1)
//f6 = (not x0 and not x1) or (x0 and not x1)
module CCGRTT572_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;

	assign f0 = d1;
	or (d1, d2, d5);
	and (d2, d3, d4);
	not (d3, x0);
	not (d4, x1);
	or (d5, d6, d7);
	and (d6, x0, d4);
	and (d7, x0, x1);
	assign f1 = d8;
	or (d8, d7, d9);
	and (d9, d3, x1);
	assign f2 = d10;
	or (d10, d6, d9);
	assign f3 = d9;
	assign f4 = 1'b0;
	assign f5 = d5;
	assign f6 = d11;
	or (d11, d2, d6);
endmodule
