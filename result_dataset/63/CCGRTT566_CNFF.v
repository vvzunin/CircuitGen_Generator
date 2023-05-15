//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT566_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

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
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d20);
	or (d15, d16, d17);
	not (d16, x0);
	or (d17, x1, d18);
	or (d18, x3, d19);
	not (d19, x2);
	and (d20, d21, d22);
	or (d21, d12, d16);
	or (d22, d16, d23);
	or (d23, d8, d13);
	assign f1 = d24;
	and (d24, d2, d25);
	and (d25, d26, d27);
	or (d26, x0, d17);
	and (d27, d11, d28);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, d13, d18);
	and (d31, d32, d33);
	or (d32, d3, d16);
	and (d33, d15, d34);
	and (d34, d35, d38);
	or (d35, d16, d36);
	or (d36, x1, d37);
	or (d37, d9, d19);
	and (d38, d21, d39);
	and (d39, d22, d40);
	or (d40, d16, d41);
	or (d41, d13, d37);
	assign f2 = d42;
	and (d42, d2, d43);
	and (d43, d26, d44);
	and (d44, d45, d46);
	or (d45, x0, d36);
	and (d46, d47, d48);
	or (d47, x0, d23);
	and (d48, d49, d50);
	or (d49, x0, d41);
	and (d50, d15, d51);
	and (d51, d35, d52);
	and (d52, d21, d53);
	and (d53, d40, d54);
	or (d54, d16, d30);
	assign f3 = d55;
	and (d55, d6, d56);
	and (d56, d11, d57);
	and (d57, d47, d58);
	and (d58, d52, d59);
	or (d59, d7, d16);
	assign f4 = d60;
	and (d60, d26, d61);
	and (d61, d45, d62);
	and (d62, d11, d63);
	and (d63, d47, d64);
	and (d64, d49, d65);
	and (d65, d21, d59);
	assign f5 = d66;
	and (d66, d2, d67);
	and (d67, d6, d68);
	and (d68, d26, d69);
	and (d69, d45, d70);
	and (d70, d11, d71);
	and (d71, d47, d72);
	and (d72, d38, d49);
endmodule
