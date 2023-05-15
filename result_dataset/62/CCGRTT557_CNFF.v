//f0 = (x0 or not x1)
//f1 = (x0 or x1) and (not x0 or x1)
//f2 = (x0 or x1) and (not x0 or not x1)
//f3 = (x0 or x1) and (not x0 or x1) and (not x0 or not x1)
//f4 = 1'b0
//f5 = (x0 or x1) and (x0 or not x1)
//f6 = (x0 or not x1) and (not x0 or not x1)
module CCGRTT557_CNFF(
	input x0, x1,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12;

	assign f0 = d1;
	or (d1, x0, d2);
	not (d2, x1);
	assign f1 = d3;
	and (d3, d4, d5);
	or (d4, x0, x1);
	or (d5, x1, d6);
	not (d6, x0);
	assign f2 = d7;
	and (d7, d4, d8);
	or (d8, d2, d6);
	assign f3 = d9;
	and (d9, d4, d10);
	and (d10, d5, d8);
	assign f4 = 1'b0;
	assign f5 = d11;
	and (d11, d1, d4);
	assign f6 = d12;
	and (d12, d1, d8);
endmodule
