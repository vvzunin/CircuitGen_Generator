//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1901_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

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
	and (d16, d17, d21);
	or (d17, d13, d18);
	or (d18, d19, d20);
	not (d19, x1);
	or (d20, x2, x3);
	and (d21, d22, d24);
	or (d22, d13, d23);
	or (d23, d15, d19);
	or (d24, d13, d25);
	or (d25, d9, d19);
	assign f1 = d26;
	and (d26, d27, d28);
	or (d27, x0, d25);
	and (d28, d29, d31);
	or (d29, d13, d30);
	or (d30, x1, d20);
	and (d31, d32, d33);
	or (d32, d3, d13);
	and (d33, d17, d22);
	assign f2 = d34;
	and (d34, d35, d36);
	or (d35, x0, d30);
	and (d36, d37, d38);
	or (d37, x0, d23);
	and (d38, d27, d39);
	and (d39, d29, d40);
	and (d40, d32, d41);
	and (d41, d12, d42);
	and (d42, d21, d43);
	or (d43, d13, d44);
	or (d44, d4, d19);
	assign f3 = d45;
	and (d45, d2, d46);
	and (d46, d27, d31);
	assign f4 = d47;
	and (d47, d35, d48);
	and (d48, d2, d49);
	and (d49, d50, d51);
	or (d50, x0, d14);
	and (d51, d7, d52);
	and (d52, d53, d54);
	or (d53, x0, d18);
	and (d54, d37, d55);
	and (d55, d27, d56);
	and (d56, d12, d29);
	assign f5 = d57;
	and (d57, d50, d58);
	and (d58, d59, d60);
	or (d59, x0, d44);
	and (d60, d37, d61);
	and (d61, d29, d62);
	and (d62, d32, d63);
	and (d63, d12, d64);
	and (d64, d33, d65);
	or (d65, d8, d13);
	assign f6 = d66;
	and (d66, d35, d67);
	and (d67, d7, d68);
	and (d68, d53, d69);
	and (d69, d59, d64);
endmodule
