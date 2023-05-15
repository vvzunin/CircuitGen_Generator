//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1621_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, d5, d10);
	and (d20, d21, d23);
	or (d21, d3, d22);
	not (d22, x0);
	and (d23, d24, d25);
	or (d24, d8, d22);
	and (d25, d26, d28);
	or (d26, d22, d27);
	or (d27, d4, d14);
	or (d28, d18, d22);
	assign f1 = d29;
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, x1, d15);
	and (d32, d2, d33);
	and (d33, d7, d34);
	and (d34, d17, d35);
	and (d35, d24, d36);
	and (d36, d28, d37);
	or (d37, d13, d22);
	assign f2 = d38;
	and (d38, d30, d39);
	and (d39, d2, d40);
	and (d40, d7, d41);
	and (d41, d42, d44);
	or (d42, x0, d43);
	or (d43, x1, d19);
	and (d44, d17, d45);
	and (d45, d46, d47);
	or (d46, d22, d31);
	and (d47, d21, d48);
	and (d48, d49, d50);
	or (d49, d22, d43);
	and (d50, d28, d51);
	or (d51, d22, d52);
	or (d52, d9, d14);
	assign f3 = d53;
	and (d53, d30, d54);
	and (d54, d2, d55);
	and (d55, d42, d56);
	and (d56, d12, d57);
	and (d57, d58, d59);
	or (d58, x0, d27);
	and (d59, d60, d61);
	or (d60, x0, d52);
	and (d61, d46, d51);
endmodule
