//f0 = (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f4 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1737_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, d6);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, d9, d10);
	not (d9, x0);
	or (d10, x1, d11);
	or (d11, x2, x3);
	and (d12, d13, d15);
	or (d13, d9, d14);
	or (d14, x1, d5);
	and (d15, d16, d20);
	or (d16, d9, d17);
	or (d17, x1, d18);
	or (d18, x3, d19);
	not (d19, x2);
	and (d20, d21, d24);
	or (d21, d9, d22);
	or (d22, x1, d23);
	or (d23, d6, d19);
	and (d24, d25, d27);
	or (d25, d9, d26);
	or (d26, d4, d11);
	and (d27, d28, d29);
	or (d28, d3, d9);
	or (d29, d9, d30);
	or (d30, d4, d18);
	assign f1 = d31;
	and (d31, d32, d33);
	or (d32, x0, d10);
	and (d33, d34, d35);
	or (d34, x0, d14);
	and (d35, d2, d36);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d4, d23);
	and (d39, d21, d28);
	assign f2 = d40;
	and (d40, d32, d41);
	and (d41, d34, d42);
	and (d42, d43, d44);
	or (d43, x0, d17);
	and (d44, d45, d46);
	or (d45, x0, d30);
	and (d46, d37, d47);
	and (d47, d8, d48);
	and (d48, d16, d49);
	or (d49, d9, d38);
	assign f3 = d50;
	and (d50, d32, d51);
	and (d51, d52, d53);
	or (d52, x0, d22);
	and (d53, d2, d54);
	and (d54, d37, d55);
	and (d55, d8, d21);
	assign f4 = d56;
	and (d56, d2, d57);
	and (d57, d45, d58);
	and (d58, d37, d59);
	and (d59, d8, d60);
	and (d60, d13, d61);
	and (d61, d16, d27);
endmodule
