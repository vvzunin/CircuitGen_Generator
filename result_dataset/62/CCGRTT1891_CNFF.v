//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1891_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x3, d9);
	not (d9, x2);
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d13, d17);
	or (d17, x2, d18);
	not (d18, x3);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d8, d13);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, d13, d25);
	or (d25, d9, d18);
	and (d26, d27, d29);
	or (d27, d3, d28);
	not (d28, x0);
	and (d29, d30, d32);
	or (d30, d28, d31);
	or (d31, x1, d17);
	and (d32, d33, d34);
	or (d33, d7, d28);
	and (d34, d35, d37);
	or (d35, d28, d36);
	or (d36, x1, d25);
	and (d37, d38, d39);
	or (d38, d16, d28);
	or (d39, d21, d28);
	assign f1 = d40;
	and (d40, d2, d41);
	and (d41, d11, d42);
	and (d42, d35, d43);
	and (d43, d44, d45);
	or (d44, d12, d28);
	and (d45, d38, d46);
	and (d46, d39, d47);
	or (d47, d24, d28);
	assign f2 = d48;
	and (d48, d11, d49);
	and (d49, d38, d44);
	assign f3 = d50;
	and (d50, d49, d51);
	or (d51, x0, d36);
	assign f4 = d52;
	and (d52, d20, d53);
	and (d53, d23, d54);
	and (d54, d30, d55);
	and (d55, d33, d56);
	and (d56, d44, d47);
	assign f5 = d57;
	and (d57, d58, d59);
	or (d58, x0, d31);
	and (d59, d6, d60);
	and (d60, d51, d61);
	and (d61, d15, d62);
	and (d62, d27, d45);
endmodule
