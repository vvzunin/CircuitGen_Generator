//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT525_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
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
	or (d8, x2, d9);
	not (d9, x3);
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, x1, d18);
	or (d18, d9, d14);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d4, d22);
	not (d22, x1);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d18, d22);
	and (d26, d27, d29);
	or (d27, d3, d28);
	not (d28, x0);
	and (d29, d30, d31);
	or (d30, d17, d28);
	and (d31, d32, d34);
	or (d32, d28, d33);
	or (d33, d8, d22);
	or (d34, d25, d28);
	assign f1 = d35;
	and (d35, d11, d36);
	and (d36, d16, d37);
	and (d37, d30, d38);
	and (d38, d32, d39);
	or (d39, d28, d40);
	or (d40, d13, d22);
	assign f2 = d41;
	and (d41, d6, d42);
	and (d42, d11, d43);
	and (d43, d16, d44);
	and (d44, d45, d46);
	or (d45, x0, d33);
	and (d46, d27, d47);
	and (d47, d30, d48);
	or (d48, d7, d28);
	assign f3 = d49;
	and (d49, d16, d50);
	and (d50, d48, d51);
	and (d51, d52, d53);
	or (d52, d12, d28);
	and (d53, d30, d54);
	and (d54, d55, d56);
	or (d55, d21, d28);
	and (d56, d34, d39);
	assign f4 = d57;
	and (d57, d16, d58);
	and (d58, d20, d59);
	and (d59, d24, d60);
	and (d60, d27, d61);
	and (d61, d48, d62);
	and (d62, d30, d63);
	and (d63, d55, d64);
	and (d64, d32, d56);
endmodule
