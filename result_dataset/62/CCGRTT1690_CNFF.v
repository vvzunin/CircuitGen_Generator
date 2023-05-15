//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1690_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

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
	and (d22, d23, d25);
	or (d23, d3, d24);
	not (d24, x0);
	and (d25, d26, d28);
	or (d26, d24, d27);
	or (d27, x1, d17);
	and (d28, d29, d30);
	or (d29, d7, d24);
	and (d30, d31, d32);
	or (d31, d12, d24);
	or (d32, d24, d33);
	or (d33, d13, d34);
	or (d34, d9, d18);
	assign f1 = d35;
	and (d35, d2, d36);
	and (d36, d6, d37);
	and (d37, d11, d38);
	and (d38, d15, d39);
	and (d39, d40, d41);
	or (d40, x0, d33);
	and (d41, d23, d42);
	and (d42, d26, d43);
	or (d43, d24, d44);
	or (d44, x1, d34);
	assign f2 = d45;
	and (d45, d2, d46);
	and (d46, d47, d48);
	or (d47, x0, d27);
	and (d48, d6, d49);
	and (d49, d23, d50);
	and (d50, d26, d51);
	and (d51, d29, d52);
	and (d52, d31, d53);
	and (d53, d32, d54);
	or (d54, d21, d24);
	assign f3 = d55;
	and (d55, d2, d56);
	and (d56, d57, d58);
	or (d57, x0, d44);
	and (d58, d15, d59);
	and (d59, d26, d60);
	and (d60, d31, d61);
	or (d61, d16, d24);
endmodule
