//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT535_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x3, d9);
	not (d9, x2);
	and (d10, d11, d16);
	or (d11, x0, d12);
	or (d12, d13, d14);
	not (d13, x1);
	or (d14, x2, d15);
	not (d15, x3);
	and (d16, d17, d19);
	or (d17, d7, d18);
	not (d18, x0);
	or (d19, d18, d20);
	or (d20, d8, d13);
	assign f1 = d21;
	and (d21, d22, d25);
	or (d22, x0, d23);
	or (d23, x1, d24);
	or (d24, d9, d15);
	and (d25, d26, d28);
	or (d26, x0, d27);
	or (d27, d4, d13);
	and (d28, d29, d31);
	or (d29, d18, d30);
	or (d30, x1, d14);
	and (d31, d17, d32);
	and (d32, d33, d34);
	or (d33, d18, d27);
	or (d34, d12, d18);
	assign f2 = d35;
	and (d35, d2, d36);
	and (d36, d37, d38);
	or (d37, x0, d30);
	and (d38, d6, d39);
	and (d39, d22, d40);
	and (d40, d11, d41);
	and (d41, d42, d44);
	or (d42, x0, d43);
	or (d43, d13, d24);
	and (d44, d29, d45);
	and (d45, d46, d47);
	or (d46, d18, d23);
	and (d47, d19, d33);
	assign f3 = d48;
	and (d48, d2, d49);
	and (d49, d37, d50);
	and (d50, d46, d51);
	and (d51, d33, d52);
	and (d52, d19, d53);
	or (d53, d18, d43);
	assign f4 = d54;
	and (d54, d2, d55);
	and (d55, d22, d56);
	and (d56, d26, d57);
	and (d57, d11, d58);
	and (d58, d59, d60);
	or (d59, x0, d20);
	and (d60, d46, d61);
	and (d61, d33, d62);
	and (d62, d34, d53);
endmodule
