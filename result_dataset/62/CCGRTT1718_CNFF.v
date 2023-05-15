//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f2 = (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1718_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d18);
	or (d16, d8, d17);
	not (d17, x0);
	and (d18, d19, d20);
	or (d19, d13, d17);
	or (d20, d17, d21);
	or (d21, d9, d14);
	assign f1 = d22;
	and (d22, d2, d23);
	and (d23, d7, d24);
	and (d24, d25, d28);
	or (d25, x0, d26);
	or (d26, x1, d27);
	or (d27, d5, d10);
	and (d28, d29, d32);
	or (d29, x0, d30);
	or (d30, d14, d31);
	or (d31, x2, x3);
	and (d32, d12, d33);
	and (d33, d34, d35);
	or (d34, x0, d21);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d14, d27);
	and (d38, d39, d40);
	or (d39, d3, d17);
	and (d40, d16, d41);
	or (d41, d17, d26);
	assign f2 = d42;
	and (d42, d39, d43);
	and (d43, d41, d44);
	and (d44, d20, d45);
	or (d45, d17, d37);
	assign f3 = d46;
	and (d46, d47, d49);
	or (d47, x0, d48);
	or (d48, x1, d31);
	and (d49, d2, d50);
	and (d50, d25, d51);
	and (d51, d29, d52);
	and (d52, d36, d53);
	and (d53, d39, d54);
	and (d54, d16, d55);
	and (d55, d44, d56);
	or (d56, d17, d30);
	assign f4 = d57;
	and (d57, d29, d58);
	and (d58, d59, d60);
	or (d59, d17, d48);
	and (d60, d39, d61);
	and (d61, d19, d44);
endmodule
