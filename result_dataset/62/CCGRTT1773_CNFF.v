//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1773_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d18);
	or (d16, x0, d17);
	or (d17, d9, d14);
	and (d18, d19, d21);
	or (d19, d3, d20);
	not (d20, x0);
	and (d21, d22, d23);
	or (d22, d8, d20);
	or (d23, d20, d24);
	or (d24, d14, d25);
	or (d25, x2, x3);
	assign f1 = d26;
	and (d26, d7, d27);
	and (d27, d16, d28);
	and (d28, d29, d32);
	or (d29, x0, d30);
	or (d30, d14, d31);
	or (d31, d5, d10);
	and (d32, d22, d33);
	and (d33, d23, d34);
	or (d34, d13, d20);
	assign f2 = d35;
	and (d35, d2, d36);
	and (d36, d16, d37);
	and (d37, d29, d38);
	and (d38, d39, d41);
	or (d39, d20, d40);
	or (d40, x1, d25);
	and (d41, d42, d43);
	or (d42, d17, d20);
	or (d43, d20, d30);
	assign f3 = d44;
	and (d44, d45, d47);
	or (d45, x0, d46);
	or (d46, x1, d31);
	and (d47, d16, d48);
	and (d48, d29, d49);
	and (d49, d39, d50);
	and (d50, d19, d51);
	and (d51, d43, d52);
	or (d52, d20, d46);
	assign f4 = d53;
	and (d53, d45, d54);
	and (d54, d55, d56);
	or (d55, x0, d24);
	and (d56, d12, d57);
	and (d57, d29, d58);
	and (d58, d39, d59);
	and (d59, d19, d60);
	and (d60, d22, d61);
	and (d61, d23, d62);
	and (d62, d34, d43);
endmodule
