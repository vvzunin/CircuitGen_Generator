//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1921_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
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
	or (d8, x2, d9);
	not (d9, x3);
	and (d10, d11, d16);
	or (d11, x0, d12);
	or (d12, d13, d14);
	not (d13, x1);
	or (d14, d9, d15);
	not (d15, x2);
	and (d16, d17, d19);
	or (d17, d7, d18);
	not (d18, x0);
	and (d19, d20, d22);
	or (d20, d18, d21);
	or (d21, x1, d14);
	and (d22, d23, d25);
	or (d23, d18, d24);
	or (d24, d8, d13);
	and (d25, d26, d29);
	or (d26, d18, d27);
	or (d27, d13, d28);
	or (d28, x3, d15);
	or (d29, d12, d18);
	assign f1 = d30;
	and (d30, d31, d32);
	or (d31, x0, d24);
	and (d32, d33, d35);
	or (d33, d18, d34);
	or (d34, x1, d28);
	and (d35, d20, d36);
	or (d36, d18, d37);
	or (d37, d4, d13);
	assign f2 = d38;
	and (d38, d2, d39);
	and (d39, d40, d41);
	or (d40, x0, d34);
	and (d41, d31, d42);
	and (d42, d33, d43);
	and (d43, d20, d44);
	and (d44, d22, d36);
	assign f3 = d45;
	and (d45, d6, d46);
	and (d46, d40, d47);
	and (d47, d48, d49);
	or (d48, x0, d21);
	and (d49, d20, d50);
	and (d50, d23, d29);
	assign f4 = d51;
	and (d51, d6, d52);
	and (d52, d40, d53);
	and (d53, d48, d54);
	and (d54, d55, d56);
	or (d55, x0, d37);
	and (d56, d31, d57);
	and (d57, d11, d58);
	and (d58, d33, d59);
	and (d59, d20, d60);
	and (d60, d23, d26);
	assign f5 = d61;
	and (d61, d2, d62);
	and (d62, d6, d63);
	and (d63, d48, d64);
	and (d64, d11, d65);
	and (d65, d66, d67);
	or (d66, d3, d18);
	and (d67, d22, d33);
	assign f6 = d68;
	and (d68, d6, d69);
	and (d69, d55, d70);
	and (d70, d66, d71);
	and (d71, d33, d50);
endmodule
