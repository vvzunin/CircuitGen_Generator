//f0 = (x0 or x1) and (not x0 or not x1)
//f1 = 1'b0
//f2 = (x0 or not x1) and (not x0 or x1)
module CCGRTT38_CNFF(
	input x0, x1,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8;

	assign f0 = d1;
	and (d1, d2, d3);
	or (d2, x0, x1);
	or (d3, d4, d5);
	not (d4, x0);
	not (d5, x1);
	assign f1 = 1'b0;
	assign f2 = d6;
	and (d6, d7, d8);
	or (d7, x0, d5);
	or (d8, x1, d4);
endmodule
