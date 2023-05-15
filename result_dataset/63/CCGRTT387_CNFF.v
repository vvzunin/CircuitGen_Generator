//f0 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2)
//f4 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or not x1 or x2)
//f5 = (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f6 = (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
module CCGRTT387_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, x2, d8);
	not (d8, x1);
	and (d9, d10, d13);
	or (d10, d11, d12);
	not (d11, x0);
	or (d12, x1, x2);
	and (d13, d14, d15);
	or (d14, d7, d11);
	or (d15, d11, d16);
	or (d16, d4, d8);
	assign f1 = d17;
	and (d17, d18, d19);
	or (d18, x0, d16);
	and (d19, d13, d20);
	or (d20, d3, d11);
	assign f2 = d21;
	and (d21, d10, d22);
	and (d22, d15, d20);
	assign f3 = d23;
	and (d23, d24, d25);
	or (d24, x0, d12);
	and (d25, d10, d14);
	assign f4 = d26;
	and (d26, d2, d27);
	and (d27, d14, d18);
	assign f5 = d28;
	and (d28, d18, d29);
	and (d29, d10, d15);
	assign f6 = d30;
	and (d30, d6, d31);
	and (d31, d18, d32);
	and (d32, d10, d33);
	and (d33, d14, d20);
endmodule
