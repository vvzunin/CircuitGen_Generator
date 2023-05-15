//f0 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1811_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d4, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d15);
	or (d12, d13, d14);
	not (d13, x0);
	or (d14, x1, d5);
	or (d15, d3, d13);
	assign f1 = d16;
	and (d16, d17, d18);
	or (d17, x0, d14);
	and (d18, d19, d23);
	or (d19, x0, d20);
	or (d20, x1, d21);
	or (d21, x2, d22);
	not (d22, x3);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, x1, d9);
	and (d26, d2, d27);
	and (d27, d7, d28);
	and (d28, d12, d29);
	and (d29, d15, d30);
	or (d30, d8, d13);
	assign f2 = d31;
	and (d31, d17, d32);
	and (d32, d24, d33);
	and (d33, d34, d37);
	or (d34, x0, d35);
	or (d35, x1, d36);
	or (d36, d10, d22);
	and (d37, d2, d38);
	and (d38, d7, d39);
	and (d39, d40, d42);
	or (d40, x0, d41);
	or (d41, d4, d36);
	and (d42, d43, d44);
	or (d43, d13, d35);
	and (d44, d30, d45);
	or (d45, d13, d46);
	or (d46, d4, d21);
	assign f3 = d47;
	and (d47, d17, d48);
	and (d48, d19, d49);
	and (d49, d50, d51);
	or (d50, x0, d46);
	and (d51, d12, d52);
	and (d52, d30, d53);
	or (d53, d13, d41);
	assign f4 = d54;
	and (d54, d19, d55);
	and (d55, d34, d56);
	and (d56, d2, d57);
	and (d57, d50, d58);
	and (d58, d7, d59);
	and (d59, d40, d60);
	and (d60, d12, d61);
	and (d61, d62, d63);
	or (d62, d13, d25);
	and (d63, d15, d53);
	assign f5 = d64;
	and (d64, d19, d65);
	and (d65, d34, d66);
	and (d66, d2, d67);
	and (d67, d12, d68);
	and (d68, d69, d70);
	or (d69, d13, d20);
	and (d70, d43, d53);
endmodule
