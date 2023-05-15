//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1513_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, d6);
	not (d5, x2);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d10, d11);
	not (d10, x1);
	or (d11, x2, x3);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d10, d15);
	or (d15, d5, x3);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d11);
	and (d20, d21, d24);
	or (d21, d18, d22);
	or (d22, x1, d23);
	or (d23, x2, d6);
	and (d24, d25, d27);
	or (d25, d18, d26);
	or (d26, x1, d15);
	and (d27, d28, d29);
	or (d28, d3, d18);
	and (d29, d30, d31);
	or (d30, d9, d18);
	or (d31, d18, d32);
	or (d32, d4, d10);
	assign f1 = d33;
	and (d33, d34, d35);
	or (d34, x0, d26);
	and (d35, d2, d36);
	and (d36, d8, d37);
	and (d37, d38, d40);
	or (d38, x0, d39);
	or (d39, d10, d23);
	and (d40, d13, d41);
	and (d41, d42, d43);
	or (d42, x0, d32);
	and (d43, d17, d44);
	and (d44, d21, d45);
	and (d45, d25, d46);
	and (d46, d28, d31);
	assign f2 = d47;
	and (d47, d48, d49);
	or (d48, x0, d22);
	and (d49, d34, d50);
	and (d50, d2, d51);
	and (d51, d8, d52);
	and (d52, d13, d53);
	and (d53, d21, d54);
	and (d54, d28, d55);
	and (d55, d30, d56);
	and (d56, d31, d57);
	or (d57, d18, d39);
endmodule
