//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1785_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, d4, d8);
	not (d8, x1);
	and (d9, d10, d14);
	or (d10, x0, d11);
	or (d11, d8, d12);
	or (d12, x2, d13);
	not (d13, x3);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d8, d17);
	or (d17, x3, d18);
	not (d18, x2);
	and (d19, d20, d22);
	or (d20, d11, d21);
	not (d21, x0);
	or (d22, d16, d21);
	assign f1 = d23;
	and (d23, d2, d24);
	and (d24, d25, d27);
	or (d25, x0, d26);
	or (d26, x1, d17);
	and (d27, d28, d31);
	or (d28, x0, d29);
	or (d29, x1, d30);
	or (d30, d13, d18);
	and (d31, d6, d32);
	and (d32, d10, d33);
	and (d33, d15, d34);
	and (d34, d35, d36);
	or (d35, d3, d21);
	and (d36, d37, d38);
	or (d37, d21, d29);
	and (d38, d39, d40);
	or (d39, d7, d21);
	or (d40, d21, d41);
	or (d41, d8, d30);
	assign f2 = d42;
	and (d42, d2, d43);
	and (d43, d44, d46);
	or (d44, x0, d45);
	or (d45, x1, d12);
	and (d46, d25, d47);
	and (d47, d28, d48);
	and (d48, d6, d49);
	and (d49, d50, d51);
	or (d50, x0, d41);
	and (d51, d52, d53);
	or (d52, d21, d45);
	and (d53, d54, d55);
	or (d54, d21, d26);
	and (d55, d20, d56);
	and (d56, d22, d40);
	assign f3 = d57;
	and (d57, d2, d58);
	and (d58, d44, d59);
	and (d59, d10, d60);
	and (d60, d50, d61);
	and (d61, d35, d62);
	and (d62, d54, d63);
	and (d63, d19, d39);
	assign f4 = d64;
	and (d64, d2, d65);
	and (d65, d44, d66);
	and (d66, d25, d67);
	and (d67, d28, d68);
	and (d68, d50, d63);
endmodule
