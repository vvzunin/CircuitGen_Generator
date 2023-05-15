//f0 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1758_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d4, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d4, d14);
	or (d14, d10, d15);
	not (d15, x3);
	and (d16, d17, d21);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d20);
	or (d20, x2, d15);
	and (d21, d22, d24);
	or (d22, d18, d23);
	or (d23, x1, d14);
	and (d24, d25, d26);
	or (d25, d3, d18);
	and (d26, d27, d29);
	or (d27, d18, d28);
	or (d28, d4, d20);
	and (d29, d30, d31);
	or (d30, d8, d18);
	or (d31, d13, d18);
	assign f1 = d32;
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, x1, d5);
	and (d35, d36, d37);
	or (d36, x0, d23);
	and (d37, d2, d38);
	and (d38, d7, d39);
	and (d39, d22, d30);
	assign f2 = d40;
	and (d40, d41, d42);
	or (d41, x0, d19);
	and (d42, d2, d43);
	and (d43, d44, d45);
	or (d44, x0, d28);
	and (d45, d29, d46);
	or (d46, d18, d34);
	assign f3 = d47;
	and (d47, d33, d48);
	and (d48, d41, d49);
	and (d49, d36, d50);
	and (d50, d44, d51);
	and (d51, d12, d52);
	and (d52, d17, d53);
	and (d53, d54, d56);
	or (d54, d18, d55);
	or (d55, x1, d9);
	and (d56, d22, d31);
	assign f4 = d57;
	and (d57, d33, d58);
	and (d58, d36, d59);
	and (d59, d12, d60);
	and (d60, d17, d61);
	and (d61, d24, d54);
endmodule
