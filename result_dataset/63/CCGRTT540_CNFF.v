//f0 = (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT540_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, d6, x3);
	not (d6, x2);
	and (d7, d8, d13);
	or (d8, d9, d10);
	not (d9, x0);
	or (d10, x1, d11);
	or (d11, x2, d12);
	not (d12, x3);
	and (d13, d14, d16);
	or (d14, d9, d15);
	or (d15, x1, d5);
	and (d16, d17, d20);
	or (d17, d9, d18);
	or (d18, x1, d19);
	or (d19, d6, d12);
	and (d20, d21, d23);
	or (d21, d9, d22);
	or (d22, d4, d11);
	and (d23, d24, d25);
	or (d24, d3, d9);
	or (d25, d9, d26);
	or (d26, d4, d19);
	assign f1 = d27;
	and (d27, d28, d29);
	or (d28, x0, d10);
	and (d29, d30, d31);
	or (d30, x0, d18);
	and (d31, d32, d33);
	or (d32, x0, d22);
	and (d33, d2, d20);
	assign f2 = d34;
	and (d34, d35, d38);
	or (d35, x0, d36);
	or (d36, x1, d37);
	or (d37, x2, x3);
	and (d38, d28, d39);
	and (d39, d40, d41);
	or (d40, x0, d15);
	and (d41, d30, d42);
	and (d42, d43, d45);
	or (d43, x0, d44);
	or (d44, d4, d37);
	and (d45, d32, d46);
	and (d46, d47, d48);
	or (d47, d9, d36);
	and (d48, d8, d16);
	assign f3 = d49;
	and (d49, d35, d50);
	and (d50, d40, d51);
	and (d51, d30, d52);
	and (d52, d43, d53);
	and (d53, d32, d54);
	and (d54, d2, d14);
	assign f4 = d55;
	and (d55, d30, d56);
	and (d56, d43, d57);
	and (d57, d2, d58);
	and (d58, d8, d59);
	and (d59, d14, d60);
	and (d60, d21, d25);
	assign f5 = d61;
	and (d61, d43, d62);
	and (d62, d32, d63);
	and (d63, d2, d64);
	and (d64, d65, d66);
	or (d65, x0, d26);
	and (d66, d17, d67);
	and (d67, d21, d24);
endmodule
