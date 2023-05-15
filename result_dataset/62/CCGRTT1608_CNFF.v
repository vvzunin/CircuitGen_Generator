//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1608_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d9, d14);
	or (d14, x2, d15);
	not (d15, x3);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d9);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d9, d22);
	or (d22, d5, d15);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d10);
	and (d27, d28, d30);
	or (d28, d25, d29);
	or (d29, x1, d14);
	and (d30, d31, d32);
	or (d31, d3, d25);
	and (d32, d33, d35);
	or (d33, d25, d34);
	or (d34, x1, d22);
	and (d35, d36, d37);
	or (d36, d8, d25);
	and (d37, d38, d39);
	or (d38, d13, d25);
	and (d39, d40, d41);
	or (d40, d18, d25);
	or (d41, d21, d25);
	assign f1 = d42;
	and (d42, d43, d44);
	or (d43, x0, d26);
	and (d44, d2, d45);
	and (d45, d46, d47);
	or (d46, x0, d34);
	and (d47, d12, d48);
	and (d48, d17, d49);
	and (d49, d28, d31);
	assign f2 = d50;
	and (d50, d43, d51);
	and (d51, d52, d53);
	or (d52, x0, d29);
	and (d53, d46, d54);
	and (d54, d7, d55);
	and (d55, d12, d56);
	and (d56, d20, d57);
	and (d57, d28, d58);
	and (d58, d31, d59);
	and (d59, d38, d40);
	assign f3 = d60;
	and (d60, d2, d61);
	and (d61, d7, d62);
	and (d62, d12, d63);
	and (d63, d24, d64);
	and (d64, d28, d65);
	and (d65, d31, d66);
	and (d66, d36, d39);
endmodule
