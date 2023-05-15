//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT583_CNFF(
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
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d13, d17);
	or (d17, d9, d18);
	not (d18, x2);
	and (d19, d20, d22);
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d24);
	or (d23, d7, d21);
	and (d24, d25, d28);
	or (d25, d21, d26);
	or (d26, x1, d27);
	or (d27, x3, d18);
	and (d28, d29, d31);
	or (d29, d21, d30);
	or (d30, d8, d13);
	and (d31, d32, d34);
	or (d32, d21, d33);
	or (d33, d13, d27);
	or (d34, d16, d21);
	assign f1 = d35;
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, x1, d17);
	and (d38, d39, d40);
	or (d39, x0, d30);
	and (d40, d25, d41);
	and (d41, d34, d42);
	or (d42, d12, d21);
	assign f2 = d43;
	and (d43, d44, d45);
	or (d44, x0, d26);
	and (d45, d11, d46);
	and (d46, d15, d47);
	and (d47, d23, d40);
	assign f3 = d48;
	and (d48, d2, d49);
	and (d49, d6, d50);
	and (d50, d44, d51);
	and (d51, d36, d52);
	and (d52, d11, d53);
	and (d53, d54, d55);
	or (d54, x0, d33);
	and (d55, d15, d56);
	and (d56, d20, d57);
	and (d57, d23, d42);
	assign f4 = d58;
	and (d58, d2, d59);
	and (d59, d44, d60);
	and (d60, d39, d61);
	and (d61, d20, d28);
	assign f5 = d62;
	and (d62, d44, d63);
	and (d63, d36, d64);
	and (d64, d39, d65);
	and (d65, d15, d66);
	and (d66, d42, d67);
	and (d67, d29, d34);
	assign f6 = d68;
	and (d68, d6, d69);
	and (d69, d11, d70);
	and (d70, d15, d71);
	and (d71, d23, d32);
endmodule
