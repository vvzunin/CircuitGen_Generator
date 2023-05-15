//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1500_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, d9, d10);
	not (d9, x2);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x3, d9);
	and (d16, d17, d21);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d20);
	or (d20, x2, d10);
	and (d21, d22, d24);
	or (d22, d18, d23);
	or (d23, x1, d15);
	or (d24, d18, d25);
	or (d25, d4, d14);
	assign f1 = d26;
	and (d26, d2, d27);
	and (d27, d28, d29);
	or (d28, x0, d19);
	and (d29, d30, d31);
	or (d30, x0, d25);
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, d14, d20);
	and (d34, d12, d35);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d8, d14);
	and (d38, d39, d40);
	or (d39, d3, d18);
	and (d40, d17, d41);
	and (d41, d42, d43);
	or (d42, d13, d18);
	or (d43, d18, d37);
	assign f2 = d44;
	and (d44, d28, d45);
	and (d45, d46, d47);
	or (d46, x0, d23);
	and (d47, d32, d48);
	and (d48, d17, d49);
	and (d49, d24, d43);
endmodule
