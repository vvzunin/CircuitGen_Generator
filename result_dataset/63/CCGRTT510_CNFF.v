//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT510_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d14);
	and (d19, d20, d23);
	or (d20, d21, d22);
	not (d21, x0);
	or (d22, x1, d15);
	and (d23, d24, d25);
	or (d24, d3, d21);
	and (d25, d26, d27);
	or (d26, d8, d21);
	and (d27, d28, d31);
	or (d28, d21, d29);
	or (d29, x1, d30);
	or (d30, d5, d10);
	and (d31, d32, d33);
	or (d32, d18, d21);
	and (d33, d34, d36);
	or (d34, d21, d35);
	or (d35, d9, d14);
	or (d36, d21, d37);
	or (d37, d14, d30);
	assign f1 = d38;
	and (d38, d39, d40);
	or (d39, x0, d22);
	and (d40, d7, d41);
	and (d41, d12, d42);
	and (d42, d17, d43);
	and (d43, d44, d45);
	or (d44, x0, d37);
	and (d45, d20, d46);
	and (d46, d26, d47);
	and (d47, d48, d49);
	or (d48, d13, d21);
	and (d49, d32, d34);
	assign f2 = d50;
	and (d50, d39, d51);
	and (d51, d2, d52);
	and (d52, d7, d53);
	and (d53, d54, d55);
	or (d54, x0, d35);
	and (d55, d26, d56);
	and (d56, d32, d48);
	assign f3 = d57;
	and (d57, d39, d58);
	and (d58, d2, d59);
	and (d59, d54, d60);
	and (d60, d26, d49);
	assign f4 = d61;
	and (d61, d7, d62);
	and (d62, d12, d63);
	and (d63, d17, d64);
	and (d64, d54, d65);
	and (d65, d44, d66);
	and (d66, d24, d46);
endmodule
