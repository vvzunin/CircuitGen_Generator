//f0 = 1'b0
//f1 = (x0 and x1)
//f2 = (not x0 and not x1)
//f3 = (not x0 and not x1) or (not x0 and x1) or (x0 and not x1)
//f4 = 1'b0
//f5 = (not x0 and x1)
//f6 = (not x0 and not x1) or (not x0 and x1)
//f7 = 1'b0
module CCGRTT205_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9;

	assign f0 = 1'b0;
	assign f1 = d1;
	and (d1, x0, x1);
	assign f2 = d2;
	and (d2, d3, d4);
	not (d3, x0);
	not (d4, x1);
	assign f3 = d5;
	or (d5, d2, d6);
	or (d6, d7, d8);
	and (d7, x1, d3);
	and (d8, x0, d4);
	assign f4 = 1'b0;
	assign f5 = d7;
	assign f6 = d9;
	or (d9, d2, d7);
	assign f7 = 1'b0;
endmodule
