//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
module CCGRTT1617_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, d9, d14);
	not (d14, x3);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d18, d22);
	or (d22, x2, d14);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d8, d18);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d13, d18);
	and (d29, d30, d32);
	or (d30, d3, d31);
	not (d31, x0);
	and (d32, d33, d35);
	or (d33, d31, d34);
	or (d34, x1, d22);
	and (d35, d36, d37);
	or (d36, d21, d31);
	or (d37, d25, d31);
	assign f1 = d38;
	and (d38, d6, d39);
	and (d39, d16, d40);
	and (d40, d20, d41);
	and (d41, d24, d42);
	and (d42, d27, d43);
	and (d43, d30, d44);
	and (d44, d33, d45);
	and (d45, d46, d47);
	or (d46, d12, d31);
	and (d47, d48, d49);
	or (d48, d17, d31);
	and (d49, d37, d50);
	or (d50, d28, d31);
	assign f2 = d51;
	and (d51, d2, d52);
	and (d52, d53, d54);
	or (d53, x0, d34);
	and (d54, d6, d55);
	and (d55, d16, d56);
	and (d56, d20, d57);
	and (d57, d24, d58);
	and (d58, d27, d59);
	and (d59, d33, d60);
	or (d60, d7, d31);
	assign f3 = d61;
	and (d61, d6, d62);
	and (d62, d11, d63);
	and (d63, d16, d64);
	and (d64, d20, d58);
endmodule
