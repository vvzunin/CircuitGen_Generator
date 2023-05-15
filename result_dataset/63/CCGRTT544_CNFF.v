//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT544_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, d13, d14);
	not (d13, x0);
	or (d14, x1, d15);
	or (d15, x3, d10);
	and (d16, d17, d18);
	or (d17, d8, d13);
	and (d18, d19, d23);
	or (d19, d13, d20);
	or (d20, d21, d22);
	not (d21, x1);
	or (d22, x2, x3);
	and (d23, d24, d26);
	or (d24, d13, d25);
	or (d25, d15, d21);
	or (d26, d13, d27);
	or (d27, d9, d21);
	assign f1 = d28;
	and (d28, d2, d29);
	and (d29, d7, d30);
	and (d30, d31, d32);
	or (d31, x0, d20);
	and (d32, d12, d24);
	assign f2 = d33;
	and (d33, d34, d36);
	or (d34, x0, d35);
	or (d35, x1, d22);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d4, d21);
	and (d39, d40, d41);
	or (d40, x0, d27);
	and (d41, d42, d43);
	or (d42, d13, d35);
	and (d43, d17, d19);
	assign f3 = d44;
	and (d44, d7, d45);
	and (d45, d31, d46);
	and (d46, d42, d47);
	and (d47, d18, d48);
	or (d48, d3, d13);
	assign f4 = d49;
	and (d49, d34, d50);
	and (d50, d2, d51);
	and (d51, d37, d52);
	and (d52, d53, d54);
	or (d53, x0, d25);
	and (d54, d40, d55);
	and (d55, d42, d56);
	and (d56, d48, d57);
	and (d57, d12, d58);
	and (d58, d17, d59);
	or (d59, d13, d38);
	assign f5 = d60;
	and (d60, d2, d61);
	and (d61, d53, d62);
	and (d62, d40, d63);
	and (d63, d42, d64);
	and (d64, d12, d65);
	and (d65, d24, d59);
endmodule
