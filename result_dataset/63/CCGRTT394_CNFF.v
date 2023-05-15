//f0 = (not x0 or not x1 or x2)
//f1 = (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f3 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2)
//f5 = (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f6 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f7 = (x0 or x1 or x2) and (x0 or not x1 or not x2)
module CCGRTT394_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32;

	assign f0 = d1;
	or (d1, d2, d3);
	not (d2, x0);
	or (d3, d4, x2);
	not (d4, x1);
	assign f1 = d5;
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, d4, d8);
	not (d8, x2);
	and (d9, d10, d12);
	or (d10, d2, d11);
	or (d11, x1, x2);
	and (d12, d13, d15);
	or (d13, d2, d14);
	or (d14, x1, d8);
	and (d15, d1, d16);
	or (d16, d2, d7);
	assign f2 = d17;
	and (d17, d6, d18);
	and (d18, d10, d19);
	and (d19, d1, d13);
	assign f3 = d20;
	and (d20, d21, d22);
	or (d21, x0, d11);
	and (d22, d23, d24);
	or (d23, x0, d14);
	and (d24, d6, d12);
	assign f4 = d25;
	and (d25, d26, d27);
	or (d26, x0, d3);
	and (d27, d6, d10);
	assign f5 = d28;
	and (d28, d10, d29);
	and (d29, d13, d16);
	assign f6 = d30;
	and (d30, d23, d31);
	and (d31, d24, d26);
	assign f7 = d32;
	and (d32, d6, d21);
endmodule
