//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1928_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d9, d14);
	or (d14, x2, d15);
	not (d15, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d9, d19);
	or (d19, d5, d15);
	and (d20, d21, d24);
	or (d21, d22, d23);
	not (d22, x0);
	or (d23, x1, d14);
	and (d24, d25, d26);
	or (d25, d3, d22);
	and (d26, d27, d29);
	or (d27, d22, d28);
	or (d28, d4, d9);
	or (d29, d18, d22);
	assign f1 = d30;
	and (d30, d31, d32);
	or (d31, x0, d23);
	and (d32, d2, d33);
	and (d33, d34, d36);
	or (d34, x0, d35);
	or (d35, x1, d19);
	and (d36, d37, d38);
	or (d37, x0, d28);
	and (d38, d26, d39);
	or (d39, d22, d35);
	assign f2 = d40;
	and (d40, d7, d41);
	and (d41, d42, d44);
	or (d42, d22, d43);
	or (d43, x1, d10);
	and (d44, d21, d45);
	and (d45, d46, d47);
	or (d46, d8, d22);
	or (d47, d13, d22);
	assign f3 = d48;
	and (d48, d49, d50);
	or (d49, x0, d43);
	and (d50, d31, d51);
	and (d51, d34, d52);
	and (d52, d17, d53);
	and (d53, d21, d54);
	and (d54, d46, d55);
	and (d55, d29, d47);
	assign f4 = d56;
	and (d56, d31, d57);
	and (d57, d7, d58);
	and (d58, d37, d59);
	and (d59, d17, d60);
	and (d60, d21, d47);
	assign f5 = d61;
	and (d61, d49, d62);
	and (d62, d31, d63);
	and (d63, d2, d64);
	and (d64, d7, d65);
	and (d65, d37, d66);
	and (d66, d42, d67);
	and (d67, d21, d68);
	and (d68, d29, d39);
	assign f6 = d69;
	and (d69, d31, d70);
	and (d70, d34, d71);
	and (d71, d12, d72);
	and (d72, d17, d29);
endmodule
