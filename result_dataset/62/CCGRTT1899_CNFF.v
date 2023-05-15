//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1899_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, d9, d14);
	not (d14, x3);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d13, d18);
	and (d22, d23, d25);
	or (d23, d3, d24);
	not (d24, x0);
	and (d25, d26, d27);
	or (d26, d12, d24);
	or (d27, d24, d28);
	or (d28, d18, d29);
	or (d29, x2, d14);
	assign f1 = d30;
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, x1, d29);
	and (d33, d11, d34);
	and (d34, d23, d35);
	and (d35, d36, d37);
	or (d36, d24, d32);
	and (d37, d38, d39);
	or (d38, d17, d24);
	and (d39, d27, d40);
	or (d40, d21, d24);
	assign f2 = d41;
	and (d41, d11, d42);
	and (d42, d20, d43);
	and (d43, d36, d44);
	and (d44, d38, d45);
	and (d45, d27, d46);
	and (d46, d40, d47);
	or (d47, d24, d48);
	or (d48, d8, d18);
	assign f3 = d49;
	and (d49, d6, d50);
	and (d50, d16, d51);
	and (d51, d52, d53);
	or (d52, x0, d48);
	and (d53, d36, d54);
	and (d54, d55, d56);
	or (d55, d7, d24);
	and (d56, d26, d38);
	assign f4 = d57;
	and (d57, d31, d58);
	and (d58, d6, d59);
	and (d59, d52, d60);
	and (d60, d36, d61);
	and (d61, d40, d55);
	assign f5 = d62;
	and (d62, d2, d63);
	and (d63, d31, d64);
	and (d64, d6, d65);
	and (d65, d66, d67);
	or (d66, x0, d28);
	and (d67, d20, d68);
	and (d68, d23, d69);
	and (d69, d36, d70);
	and (d70, d55, d71);
	and (d71, d26, d40);
endmodule
