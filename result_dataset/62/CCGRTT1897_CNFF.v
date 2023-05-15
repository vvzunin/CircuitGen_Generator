//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f1 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1897_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, d8, d9);
	not (d8, x1);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d17);
	or (d12, d13, d14);
	not (d13, x0);
	or (d14, x1, d15);
	or (d15, x2, d16);
	not (d16, x3);
	or (d17, d13, d18);
	or (d18, x1, d9);
	assign f1 = d19;
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, x1, d22);
	or (d22, d10, d16);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d4, d8);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d8, d15);
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, d8, d22);
	and (d32, d12, d33);
	and (d33, d17, d34);
	and (d34, d35, d36);
	or (d35, d13, d21);
	and (d36, d37, d38);
	or (d37, d13, d25);
	or (d38, d7, d13);
	assign f2 = d39;
	and (d39, d40, d41);
	or (d40, x0, d14);
	and (d41, d17, d27);
	assign f3 = d42;
	and (d42, d2, d43);
	and (d43, d20, d44);
	and (d44, d45, d46);
	or (d45, d3, d13);
	and (d46, d12, d47);
	and (d47, d48, d49);
	or (d48, d13, d28);
	or (d49, d13, d31);
	assign f4 = d50;
	and (d50, d2, d51);
	and (d51, d20, d52);
	and (d52, d24, d53);
	and (d53, d6, d54);
	and (d54, d45, d55);
	and (d55, d12, d56);
	and (d56, d17, d35);
	assign f5 = d57;
	and (d57, d2, d58);
	and (d58, d59, d60);
	or (d59, x0, d18);
	and (d60, d24, d61);
	and (d61, d27, d62);
	and (d62, d30, d63);
	and (d63, d45, d64);
	and (d64, d12, d65);
	and (d65, d38, d48);
endmodule
