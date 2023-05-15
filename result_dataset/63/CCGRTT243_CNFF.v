//f0 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT243_CNFF(
	input x0, x1, x2,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d9);
	or (d5, x0, d6);
	or (d6, d7, d8);
	not (d7, x1);
	not (d8, x2);
	and (d9, d10, d12);
	or (d10, d3, d11);
	not (d11, x0);
	and (d12, d13, d15);
	or (d13, d11, d14);
	or (d14, x1, d8);
	and (d15, d16, d18);
	or (d16, d11, d17);
	or (d17, x2, d7);
	or (d18, d6, d11);
	assign f1 = d19;
	and (d19, d2, d20);
	and (d20, d21, d22);
	or (d21, x0, d14);
	and (d22, d23, d24);
	or (d23, x0, d17);
	and (d24, d5, d25);
	and (d25, d13, d18);
	assign f2 = d26;
	and (d26, d21, d27);
	and (d27, d12, d23);
endmodule
