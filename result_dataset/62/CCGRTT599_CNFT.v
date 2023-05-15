//f0 = (not x0 and x1) or (x0 and x1)
//f1 = (not x0 and not x1) or (not x0 and x1)
//f2 = (not x0 and x1) or (x0 and not x1)
//f3 = (x0 and not x1) or (x0 and x1)
//f4 = (not x0 and not x1) or (not x0 and x1) or (x0 and x1)
//f5 = (x0 and not x1) or (x0 and x1)
//f6 = (not x0 and not x1) or (x0 and not x1) or (x0 and x1)
module CCGRTT599_CNFT(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12;

	assign f0 = d1;
	or (d1, d2, d4);
	and (d2, d3, x1);
	not (d3, x0);
	and (d4, x0, x1);
	assign f1 = d5;
	or (d5, d2, d6);
	and (d6, d3, d7);
	not (d7, x1);
	assign f2 = d8;
	or (d8, d2, d9);
	and (d9, x0, d7);
	assign f3 = d10;
	or (d10, d4, d9);
	assign f4 = d11;
	or (d11, d1, d6);
	assign f5 = d10;
	assign f6 = d12;
	or (d12, d6, d10);
endmodule
