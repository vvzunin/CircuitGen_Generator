//f0 = 1'b1
//f1 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f2 = (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2)
//f5 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
module CCGRTT1149_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32;

	assign f0 = 1'b1;
	assign f1 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d8);
	or (d5, x0, d6);
	or (d6, x2, d7);
	not (d7, x1);
	and (d8, d9, d12);
	or (d9, x0, d10);
	or (d10, d7, d11);
	not (d11, x2);
	and (d12, d13, d15);
	or (d13, d3, d14);
	not (d14, x0);
	or (d15, d14, d16);
	or (d16, x1, d11);
	assign f2 = d17;
	and (d17, d18, d19);
	or (d18, x0, d16);
	and (d19, d13, d20);
	and (d20, d21, d22);
	or (d21, d6, d14);
	or (d22, d10, d14);
	assign f3 = d23;
	and (d23, d5, d24);
	and (d24, d9, d25);
	and (d25, d15, d20);
	assign f4 = d26;
	and (d26, d2, d27);
	and (d27, d5, d15);
	assign f5 = d28;
	and (d28, d2, d29);
	and (d29, d18, d30);
	and (d30, d5, d31);
	and (d31, d13, d32);
	and (d32, d15, d21);
endmodule
