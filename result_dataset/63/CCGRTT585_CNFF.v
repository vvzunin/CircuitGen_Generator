//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT585_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73;

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
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, d10);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d15);
	and (d20, d21, d23);
	or (d21, d18, d22);
	or (d22, d4, d14);
	and (d23, d24, d25);
	or (d24, d13, d18);
	or (d25, d18, d26);
	or (d26, d14, d27);
	or (d27, x3, d9);
	assign f1 = d28;
	and (d28, d2, d29);
	and (d29, d30, d31);
	or (d30, x0, d19);
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, x1, d27);
	and (d34, d6, d35);
	and (d35, d36, d37);
	or (d36, d3, d18);
	and (d37, d38, d39);
	or (d38, d7, d18);
	and (d39, d24, d40);
	and (d40, d25, d41);
	or (d41, d18, d42);
	or (d42, d8, d14);
	assign f2 = d43;
	and (d43, d44, d45);
	or (d44, x0, d22);
	and (d45, d12, d46);
	and (d46, d39, d47);
	or (d47, x0, d26);
	assign f3 = d48;
	and (d48, d32, d49);
	and (d49, d47, d50);
	and (d50, d36, d51);
	and (d51, d23, d38);
	assign f4 = d52;
	and (d52, d30, d53);
	and (d53, d44, d54);
	and (d54, d47, d55);
	and (d55, d56, d57);
	or (d56, x0, d42);
	and (d57, d36, d58);
	and (d58, d17, d59);
	and (d59, d25, d60);
	or (d60, d18, d33);
	assign f5 = d61;
	and (d61, d2, d62);
	and (d62, d32, d63);
	and (d63, d6, d64);
	and (d64, d47, d65);
	and (d65, d36, d66);
	and (d66, d60, d67);
	and (d67, d21, d40);
	assign f6 = d68;
	and (d68, d30, d69);
	and (d69, d32, d70);
	and (d70, d44, d71);
	and (d71, d56, d72);
	and (d72, d36, d73);
	and (d73, d17, d39);
endmodule
