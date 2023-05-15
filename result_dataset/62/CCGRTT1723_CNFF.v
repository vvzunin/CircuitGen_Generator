//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1723_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d8, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d24);
	or (d23, d12, d21);
	and (d24, d25, d27);
	or (d25, d21, d26);
	or (d26, d4, d18);
	and (d27, d28, d29);
	or (d28, d17, d21);
	or (d29, d21, d30);
	or (d30, d13, d18);
	assign f1 = d31;
	and (d31, d2, d32);
	and (d32, d6, d33);
	and (d33, d11, d34);
	and (d34, d35, d38);
	or (d35, x0, d36);
	or (d36, x1, d37);
	or (d37, d9, d14);
	and (d38, d39, d40);
	or (d39, x0, d26);
	and (d40, d41, d43);
	or (d41, x0, d42);
	or (d42, d18, d37);
	and (d43, d20, d44);
	and (d44, d24, d45);
	or (d45, d21, d36);
	assign f2 = d46;
	and (d46, d6, d47);
	and (d47, d11, d48);
	and (d48, d35, d49);
	and (d49, d50, d51);
	or (d50, x0, d30);
	and (d51, d20, d52);
	and (d52, d53, d54);
	or (d53, d7, d21);
	or (d54, d21, d42);
	assign f3 = d55;
	and (d55, d6, d56);
	and (d56, d39, d57);
	and (d57, d50, d58);
	and (d58, d41, d59);
	and (d59, d53, d60);
	and (d60, d23, d61);
	and (d61, d45, d62);
	and (d62, d25, d63);
	and (d63, d28, d54);
	assign f4 = d64;
	and (d64, d2, d65);
	and (d65, d11, d66);
	and (d66, d50, d67);
	and (d67, d41, d68);
	and (d68, d45, d54);
endmodule
