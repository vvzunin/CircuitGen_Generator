//f0 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f1 = (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT836_CNFF(
	input x0, x1, x2,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d8);
	or (d5, x0, d6);
	or (d6, x1, d7);
	not (d7, x2);
	and (d8, d9, d11);
	or (d9, d3, d10);
	not (d10, x0);
	and (d11, d12, d13);
	or (d12, d6, d10);
	or (d13, d10, d14);
	or (d14, x2, d15);
	not (d15, x1);
	assign f1 = d16;
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d7, d15);
	and (d19, d9, d20);
	or (d20, d10, d18);
	assign f2 = d21;
	and (d21, d2, d22);
	and (d22, d5, d19);
endmodule
