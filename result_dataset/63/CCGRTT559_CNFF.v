//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f4 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT559_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d14, d18);
	or (d18, x3, d10);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d9, d14);
	and (d22, d23, d27);
	or (d23, d24, d25);
	not (d24, x0);
	or (d25, x1, d26);
	or (d26, x2, x3);
	and (d27, d28, d29);
	or (d28, d3, d24);
	or (d29, d24, d30);
	or (d30, d14, d26);
	assign f1 = d31;
	and (d31, d32, d33);
	or (d32, x0, d25);
	and (d33, d34, d36);
	or (d34, x0, d35);
	or (d35, x1, d18);
	and (d36, d37, d38);
	or (d37, x0, d30);
	and (d38, d20, d39);
	and (d39, d23, d40);
	and (d40, d41, d42);
	or (d41, d8, d24);
	and (d42, d29, d43);
	and (d43, d44, d45);
	or (d44, d17, d24);
	or (d45, d21, d24);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d37, d48);
	and (d48, d28, d49);
	and (d49, d50, d51);
	or (d50, d24, d35);
	and (d51, d43, d52);
	or (d52, d13, d24);
	assign f3 = d53;
	and (d53, d32, d54);
	and (d54, d2, d55);
	and (d55, d7, d56);
	and (d56, d37, d57);
	and (d57, d41, d50);
	assign f4 = d58;
	and (d58, d12, d59);
	and (d59, d20, d60);
	and (d60, d23, d61);
	and (d61, d29, d52);
	assign f5 = d62;
	and (d62, d32, d63);
	and (d63, d7, d64);
	and (d64, d37, d65);
	and (d65, d12, d66);
	and (d66, d16, d27);
endmodule
