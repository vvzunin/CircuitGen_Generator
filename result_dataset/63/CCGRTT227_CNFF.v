//f0 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f1 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT227_CNFF(
	input x0, x1, x2,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d8);
	or (d5, x0, d6);
	or (d6, x2, d7);
	not (d7, x1);
	and (d8, d9, d11);
	or (d9, d3, d10);
	not (d10, x0);
	and (d11, d12, d15);
	or (d12, d10, d13);
	or (d13, x1, d14);
	not (d14, x2);
	or (d15, d6, d10);
	assign f1 = d16;
	and (d16, d2, d17);
	and (d17, d5, d18);
	and (d18, d19, d21);
	or (d19, x0, d20);
	or (d20, d7, d14);
	and (d21, d9, d22);
	or (d22, d10, d20);
endmodule
