//f0 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1870_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x2, d10);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d4, d14);
	and (d23, d24, d26);
	or (d24, d3, d25);
	not (d25, x0);
	and (d26, d27, d28);
	or (d27, d8, d25);
	or (d28, d18, d25);
	assign f1 = d29;
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, x1, d15);
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, d9, d14);
	and (d35, d36, d37);
	or (d36, d25, d31);
	and (d37, d28, d38);
	and (d38, d39, d40);
	or (d39, d22, d25);
	or (d40, d25, d34);
	assign f2 = d41;
	and (d41, d42, d44);
	or (d42, x0, d43);
	or (d43, x1, d19);
	and (d44, d7, d45);
	and (d45, d17, d46);
	and (d46, d33, d47);
	and (d47, d48, d49);
	or (d48, d25, d43);
	or (d49, d13, d25);
	assign f3 = d50;
	and (d50, d42, d51);
	and (d51, d2, d52);
	and (d52, d7, d53);
	and (d53, d24, d54);
	and (d54, d38, d49);
	assign f4 = d55;
	and (d55, d30, d56);
	and (d56, d2, d57);
	and (d57, d7, d58);
	and (d58, d17, d59);
	and (d59, d33, d60);
	and (d60, d48, d61);
	and (d61, d24, d62);
	and (d62, d49, d63);
	and (d63, d28, d40);
	assign f5 = d64;
	and (d64, d42, d65);
	and (d65, d7, d66);
	and (d66, d12, d67);
	and (d67, d17, d68);
	and (d68, d33, d69);
	and (d69, d36, d70);
	and (d70, d48, d71);
	and (d71, d27, d54);
endmodule
