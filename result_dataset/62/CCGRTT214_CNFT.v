//f0 = (x0 and x1)
//f1 = (not x0 and not x1) or (not x0 and x1) or (x0 and not x1)
//f2 = (not x0 and x1) or (x0 and not x1)
//f3 = (not x0 and not x1) or (not x0 and x1) or (x0 and x1)
module CCGRTT214_CNFT(
	input x0, x1,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;

	assign f0 = d1;
	and (d1, x0, x1);
	assign f1 = d2;
	or (d2, d3, d6);
	and (d3, d4, d5);
	not (d4, x0);
	not (d5, x1);
	or (d6, d7, d8);
	and (d7, x1, d4);
	and (d8, x0, d5);
	assign f2 = d6;
	assign f3 = d9;
	or (d9, d3, d10);
	or (d10, d1, d7);
endmodule
