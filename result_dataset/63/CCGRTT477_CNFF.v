//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT477_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, d8, d9);
	not (d8, x1);
	or (d9, x2, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d8, d14);
	or (d14, d10, d15);
	not (d15, x2);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d9);
	assign f1 = d19;
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, x1, d22);
	or (d22, x3, d15);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, x1, d14);
	and (d26, d6, d27);
	and (d27, d28, d29);
	or (d28, d17, d21);
	and (d29, d30, d31);
	or (d30, d17, d25);
	and (d31, d32, d34);
	or (d32, d17, d33);
	or (d33, d4, d8);
	and (d34, d35, d37);
	or (d35, d17, d36);
	or (d36, d8, d22);
	or (d37, d13, d17);
	assign f2 = d38;
	and (d38, d2, d39);
	and (d39, d40, d41);
	or (d40, x0, d18);
	and (d41, d20, d42);
	and (d42, d24, d43);
	and (d43, d6, d44);
	and (d44, d45, d46);
	or (d45, x0, d36);
	and (d46, d16, d47);
	and (d47, d28, d35);
endmodule
