//f0 = (not x0 or x1) and (not x0 or not x1)
//f1 = (x0 or x1) and (x0 or not x1) and (not x0 or x1)
//f2 = (x0 or x1)
//f3 = (x0 or x1) and (not x0 or x1)
//f4 = (x0 or x1)
//f5 = 1'b0
module CCGRTT412_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, d3, x1);
	not (d3, x0);
	or (d4, d3, d5);
	not (d5, x1);
	assign f1 = d6;
	and (d6, d7, d8);
	or (d7, x0, x1);
	and (d8, d2, d9);
	or (d9, x0, d5);
	assign f2 = d7;
	assign f3 = d10;
	and (d10, d2, d7);
	assign f4 = d7;
	assign f5 = 1'b0;
endmodule
