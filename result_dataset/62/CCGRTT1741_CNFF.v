//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
module CCGRTT1741_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d13, d17);
	or (d17, x2, d18);
	not (d18, x3);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d13, d22);
	or (d22, d9, d18);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d22);
	and (d27, d28, d29);
	or (d28, d16, d25);
	or (d29, d25, d30);
	or (d30, d8, d13);
	assign f1 = d31;
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, x1, d17);
	and (d34, d6, d35);
	and (d35, d15, d36);
	and (d36, d37, d38);
	or (d37, x0, d30);
	and (d38, d20, d39);
	and (d39, d40, d41);
	or (d40, d3, d25);
	and (d41, d42, d43);
	or (d42, d25, d33);
	and (d43, d24, d44);
	and (d44, d29, d45);
	or (d45, d12, d25);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d32, d48);
	and (d48, d49, d50);
	or (d49, x0, d26);
	and (d50, d15, d51);
	and (d51, d20, d52);
	and (d52, d53, d54);
	or (d53, d7, d25);
	and (d54, d24, d55);
	and (d55, d29, d56);
	or (d56, d21, d25);
	assign f3 = d57;
	and (d57, d49, d58);
	and (d58, d37, d59);
	and (d59, d20, d60);
	and (d60, d40, d61);
	and (d61, d28, d45);
	assign f4 = d62;
	and (d62, d2, d63);
	and (d63, d6, d64);
	and (d64, d11, d65);
	and (d65, d40, d66);
	and (d66, d24, d53);
endmodule
