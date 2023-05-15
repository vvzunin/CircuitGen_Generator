//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT581_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, d11);
	not (d11, x3);
	or (d12, d13, d14);
	not (d13, x0);
	or (d14, x1, d15);
	or (d15, x2, x3);
	assign f1 = d16;
	and (d16, d17, d18);
	or (d17, x0, d14);
	and (d18, d19, d21);
	or (d19, x0, d20);
	or (d20, d9, d15);
	and (d21, d7, d22);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, d9, d25);
	or (d25, d5, d11);
	and (d26, d12, d27);
	and (d27, d28, d29);
	or (d28, d13, d20);
	and (d29, d30, d31);
	or (d30, d8, d13);
	or (d31, d13, d24);
	assign f2 = d32;
	and (d32, d2, d33);
	and (d33, d19, d34);
	and (d34, d23, d35);
	and (d35, d12, d36);
	and (d36, d28, d37);
	or (d37, d13, d38);
	or (d38, d4, d9);
	assign f3 = d39;
	and (d39, d40, d42);
	or (d40, x0, d41);
	or (d41, x1, d10);
	and (d42, d23, d37);
	assign f4 = d43;
	and (d43, d2, d44);
	and (d44, d45, d47);
	or (d45, x0, d46);
	or (d46, x1, d25);
	and (d47, d7, d48);
	and (d48, d49, d50);
	or (d49, x0, d38);
	and (d50, d31, d51);
	or (d51, d3, d13);
	assign f5 = d52;
	and (d52, d40, d53);
	and (d53, d2, d54);
	and (d54, d19, d55);
	and (d55, d23, d56);
	and (d56, d57, d58);
	or (d57, d13, d41);
	and (d58, d51, d59);
	and (d59, d29, d60);
	or (d60, d13, d46);
	assign f6 = d61;
	and (d61, d40, d62);
	and (d62, d2, d63);
	and (d63, d19, d64);
	and (d64, d7, d65);
	and (d65, d49, d66);
	and (d66, d12, d67);
	and (d67, d36, d60);
endmodule
