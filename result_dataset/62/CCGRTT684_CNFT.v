//f0 = (not x0 and x1) or (x0 and not x1) or (x0 and x1)
//f1 = 1'b1
//f2 = (x0 and x1)
//f3 = (not x0 and x1) or (x0 and not x1) or (x0 and x1)
//f4 = (not x0 and not x1) or (x0 and not x1) or (x0 and x1)
//f5 = (x0 and not x1) or (x0 and x1)
//f6 = (not x0 and not x1) or (x0 and x1)
//f7 = (not x0 and not x1)
module CCGRTT684_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	assign f0 = d1;
	or (d1, d2, d4);
	and (d2, d3, x1);
	not (d3, x0);
	or (d4, d5, d7);
	and (d5, x0, d6);
	not (d6, x1);
	and (d7, x0, x1);
	assign f1 = 1'b1;
	assign f2 = d7;
	assign f3 = d1;
	assign f4 = d8;
	or (d8, d4, d9);
	and (d9, d3, d6);
	assign f5 = d4;
	assign f6 = d10;
	or (d10, d7, d9);
	assign f7 = d9;
endmodule
