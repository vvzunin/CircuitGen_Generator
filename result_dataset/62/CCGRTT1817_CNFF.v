//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1817_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, d6);
	not (d5, x2);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d10, d11);
	not (d10, x1);
	or (d11, x2, x3);
	and (d12, d13, d15);
	or (d13, x0, d14);
	or (d14, d4, d10);
	and (d15, d16, d19);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d11);
	and (d19, d20, d23);
	or (d20, d17, d21);
	or (d21, x1, d22);
	or (d22, d5, x3);
	or (d23, d9, d17);
	assign f1 = d24;
	and (d24, d25, d26);
	or (d25, x0, d21);
	and (d26, d20, d27);
	and (d27, d28, d31);
	or (d28, d17, d29);
	or (d29, d10, d30);
	or (d30, x2, d6);
	or (d31, d14, d17);
	assign f2 = d32;
	and (d32, d25, d33);
	and (d33, d8, d34);
	and (d34, d35, d36);
	or (d35, x0, d29);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d10, d22);
	and (d39, d40, d42);
	or (d40, d17, d41);
	or (d41, x1, d30);
	and (d42, d20, d43);
	and (d43, d44, d45);
	or (d44, d3, d17);
	and (d45, d23, d46);
	and (d46, d28, d47);
	and (d47, d31, d48);
	or (d48, d17, d38);
	assign f3 = d49;
	and (d49, d50, d51);
	or (d50, x0, d41);
	and (d51, d25, d52);
	and (d52, d8, d53);
	and (d53, d19, d35);
	assign f4 = d54;
	and (d54, d55, d56);
	or (d55, x0, d18);
	and (d56, d25, d57);
	and (d57, d37, d58);
	and (d58, d13, d59);
	and (d59, d16, d60);
	and (d60, d20, d61);
	and (d61, d23, d44);
	assign f5 = d62;
	and (d62, d2, d63);
	and (d63, d8, d64);
	and (d64, d40, d65);
	and (d65, d20, d66);
	and (d66, d31, d44);
endmodule
