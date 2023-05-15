//f0 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT507_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, d10);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d14);
	and (d19, d20, d24);
	or (d20, d21, d22);
	not (d21, x0);
	or (d22, x1, d23);
	or (d23, x2, x3);
	and (d24, d25, d27);
	or (d25, d21, d26);
	or (d26, x1, d15);
	and (d27, d28, d29);
	or (d28, d3, d21);
	or (d29, d13, d21);
	assign f1 = d30;
	and (d30, d31, d32);
	or (d31, x0, d22);
	and (d32, d33, d34);
	or (d33, x0, d26);
	and (d34, d12, d35);
	and (d35, d17, d36);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d9, d14);
	and (d39, d20, d40);
	and (d40, d28, d41);
	and (d41, d42, d43);
	or (d42, d8, d21);
	and (d43, d44, d46);
	or (d44, d21, d45);
	or (d45, d14, d23);
	and (d46, d29, d47);
	or (d47, d21, d38);
	assign f2 = d48;
	and (d48, d31, d49);
	and (d49, d2, d50);
	and (d50, d7, d51);
	and (d51, d17, d52);
	and (d52, d20, d43);
	assign f3 = d53;
	and (d53, d31, d54);
	and (d54, d33, d55);
	and (d55, d2, d56);
	and (d56, d25, d57);
	and (d57, d29, d44);
endmodule
