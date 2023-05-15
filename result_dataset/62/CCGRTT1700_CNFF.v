//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1700_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d9, d15);
	or (d15, d5, d11);
	and (d16, d17, d21);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d20);
	or (d20, x2, x3);
	and (d21, d22, d24);
	or (d22, d18, d23);
	or (d23, x1, d15);
	and (d24, d25, d26);
	or (d25, d8, d18);
	or (d26, d18, d27);
	or (d27, d4, d9);
	assign f1 = d28;
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, x1, d10);
	and (d31, d2, d32);
	and (d32, d33, d34);
	or (d33, x0, d23);
	and (d34, d7, d35);
	and (d35, d17, d36);
	and (d36, d37, d38);
	or (d37, d18, d30);
	and (d38, d21, d39);
	or (d39, d3, d18);
	assign f2 = d40;
	and (d40, d41, d42);
	or (d41, x0, d19);
	and (d42, d29, d43);
	and (d43, d2, d44);
	and (d44, d7, d45);
	and (d45, d46, d47);
	or (d46, x0, d27);
	and (d47, d13, d48);
	and (d48, d17, d49);
	and (d49, d37, d50);
	and (d50, d39, d51);
	and (d51, d22, d52);
	and (d52, d25, d53);
	and (d53, d26, d54);
	or (d54, d14, d18);
	assign f3 = d55;
	and (d55, d29, d56);
	and (d56, d57, d59);
	or (d57, x0, d58);
	or (d58, d9, d20);
	and (d59, d13, d60);
	and (d60, d17, d26);
	assign f4 = d61;
	and (d61, d2, d62);
	and (d62, d57, d63);
	and (d63, d7, d64);
	and (d64, d46, d65);
	and (d65, d37, d66);
	and (d66, d22, d26);
endmodule
