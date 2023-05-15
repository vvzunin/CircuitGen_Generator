//f0 = (x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1894_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, d7, d8);
	not (d7, x0);
	or (d8, x1, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d15);
	or (d12, d7, d13);
	or (d13, d4, d14);
	not (d14, x1);
	or (d15, d7, d16);
	or (d16, d14, d17);
	or (d17, d10, d18);
	not (d18, x3);
	assign f1 = d19;
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, x1, d22);
	or (d22, x2, d18);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d14, d22);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d9, d14);
	and (d29, d30, d31);
	or (d30, x0, d16);
	and (d31, d32, d33);
	or (d32, d7, d21);
	and (d33, d12, d34);
	or (d34, d7, d35);
	or (d35, x1, d17);
	assign f2 = d36;
	and (d36, d2, d37);
	and (d37, d20, d38);
	and (d38, d39, d40);
	or (d39, x0, d35);
	and (d40, d24, d41);
	and (d41, d30, d42);
	and (d42, d12, d43);
	or (d43, d3, d7);
	assign f3 = d44;
	and (d44, d45, d46);
	or (d45, x0, d8);
	and (d46, d39, d47);
	and (d47, d48, d49);
	or (d48, x0, d13);
	and (d49, d32, d50);
	and (d50, d6, d51);
	and (d51, d12, d52);
	and (d52, d53, d54);
	or (d53, d7, d25);
	or (d54, d7, d28);
	assign f4 = d55;
	and (d55, d20, d56);
	and (d56, d45, d57);
	and (d57, d24, d58);
	and (d58, d30, d59);
	and (d59, d43, d60);
	and (d60, d32, d61);
	and (d61, d6, d15);
	assign f5 = d62;
	and (d62, d2, d63);
	and (d63, d20, d64);
	and (d64, d45, d65);
	and (d65, d48, d66);
	and (d66, d32, d67);
	and (d67, d34, d54);
endmodule
