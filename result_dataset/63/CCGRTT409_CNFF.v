//f0 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or x1 or x2) and (not x0 or not x1 or x2)
//f4 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f5 = (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f6 = (x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f7 = (x0 or x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT409_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d8);
	or (d5, x0, d6);
	or (d6, x2, d7);
	not (d7, x1);
	and (d8, d9, d11);
	or (d9, d6, d10);
	not (d10, x0);
	or (d11, d10, d12);
	or (d12, d7, d13);
	not (d13, x2);
	assign f1 = d1;
	assign f2 = d14;
	and (d14, d2, d15);
	and (d15, d5, d16);
	and (d16, d17, d18);
	or (d17, d3, d10);
	and (d18, d8, d19);
	or (d19, d10, d20);
	or (d20, x1, d13);
	assign f3 = d21;
	and (d21, d2, d9);
	assign f4 = d22;
	and (d22, d2, d23);
	and (d23, d24, d25);
	or (d24, x0, d20);
	and (d25, d5, d26);
	and (d26, d27, d28);
	or (d27, x0, d12);
	and (d28, d11, d19);
	assign f5 = d29;
	and (d29, d11, d17);
	assign f6 = d30;
	and (d30, d5, d11);
	assign f7 = d31;
	and (d31, d2, d29);
endmodule
