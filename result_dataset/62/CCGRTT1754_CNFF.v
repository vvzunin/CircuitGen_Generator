//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1754_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	and (d16, d17, d19);
	or (d17, d7, d18);
	not (d18, x0);
	or (d19, d18, d20);
	or (d20, d8, d14);
	assign f1 = d21;
	and (d21, d6, d22);
	and (d22, d23, d25);
	or (d23, x0, d24);
	or (d24, d4, d14);
	and (d25, d26, d29);
	or (d26, x0, d27);
	or (d27, d14, d28);
	or (d28, x2, d10);
	and (d29, d12, d30);
	and (d30, d31, d32);
	or (d31, d3, d18);
	and (d32, d33, d35);
	or (d33, d18, d34);
	or (d34, x1, d15);
	or (d35, d18, d27);
	assign f2 = d36;
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, x1, d28);
	and (d39, d6, d40);
	and (d40, d23, d41);
	and (d41, d33, d42);
	and (d42, d17, d43);
	and (d43, d19, d44);
	or (d44, d18, d24);
	assign f3 = d45;
	and (d45, d2, d46);
	and (d46, d37, d47);
	and (d47, d26, d48);
	and (d48, d12, d49);
	and (d49, d50, d51);
	or (d50, x0, d20);
	and (d51, d31, d52);
	and (d52, d53, d54);
	or (d53, d18, d38);
	and (d54, d33, d55);
	and (d55, d35, d44);
	assign f4 = d56;
	and (d56, d57, d58);
	or (d57, x0, d34);
	and (d58, d6, d59);
	and (d59, d23, d60);
	and (d60, d50, d61);
	and (d61, d53, d62);
	and (d62, d17, d63);
	and (d63, d44, d64);
	and (d64, d19, d65);
	or (d65, d13, d18);
endmodule
