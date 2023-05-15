//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1882_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, d9, d10);
	not (d9, x2);
	not (d10, x3);
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d14, d18);
	or (d18, x2, d10);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d14, d22);
	or (d22, x3, d9);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d18);
	and (d27, d28, d30);
	or (d28, d25, d29);
	or (d29, x1, d22);
	and (d30, d31, d32);
	or (d31, d13, d25);
	and (d32, d33, d34);
	or (d33, d21, d25);
	or (d34, d25, d35);
	or (d35, d8, d14);
	assign f1 = d36;
	and (d36, d2, d37);
	and (d37, d38, d39);
	or (d38, x0, d26);
	and (d39, d12, d40);
	and (d40, d16, d41);
	and (d41, d42, d43);
	or (d42, x0, d35);
	and (d43, d24, d32);
	assign f2 = d44;
	and (d44, d2, d45);
	and (d45, d12, d46);
	and (d46, d16, d47);
	and (d47, d42, d48);
	and (d48, d49, d50);
	or (d49, d3, d25);
	and (d50, d31, d51);
	and (d51, d32, d52);
	or (d52, d17, d25);
	assign f3 = d53;
	and (d53, d2, d54);
	and (d54, d38, d55);
	and (d55, d20, d56);
	and (d56, d42, d57);
	and (d57, d28, d58);
	and (d58, d31, d33);
	assign f4 = d59;
	and (d59, d60, d61);
	or (d60, x0, d29);
	and (d61, d6, d62);
	and (d62, d12, d63);
	and (d63, d16, d64);
	and (d64, d49, d65);
	and (d65, d28, d31);
	assign f5 = d66;
	and (d66, d2, d67);
	and (d67, d38, d68);
	and (d68, d60, d69);
	and (d69, d6, d70);
	and (d70, d20, d71);
	and (d71, d42, d72);
	and (d72, d31, d34);
endmodule
