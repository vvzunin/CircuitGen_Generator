//f0 = (x0 or x1) and (not x0 or x1)
//f1 = (not x0 or x1) and (not x0 or not x1)
//f2 = (x0 or x1) and (not x0 or not x1)
//f3 = (x0 or x1) and (x0 or not x1)
//f4 = (not x0 or x1)
//f5 = (x0 or x1) and (x0 or not x1)
//f6 = (x0 or not x1)
module CCGRTT599_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	assign f0 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	or (d3, x1, d4);
	not (d4, x0);
	assign f1 = d5;
	and (d5, d3, d6);
	or (d6, d4, d7);
	not (d7, x1);
	assign f2 = d8;
	and (d8, d2, d6);
	assign f3 = d9;
	and (d9, d2, d10);
	or (d10, x0, d7);
	assign f4 = d3;
	assign f5 = d9;
	assign f6 = d10;
endmodule
