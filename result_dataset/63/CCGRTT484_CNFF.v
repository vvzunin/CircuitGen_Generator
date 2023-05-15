//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT484_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57;

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
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d26);
	or (d23, d21, d24);
	or (d24, x1, d25);
	or (d25, d9, d18);
	and (d26, d27, d28);
	or (d27, d16, d21);
	or (d28, d21, d29);
	or (d29, d13, d25);
	assign f1 = d30;
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, x1, d17);
	and (d33, d11, d34);
	and (d34, d15, d35);
	and (d35, d36, d37);
	or (d36, x0, d29);
	and (d37, d38, d39);
	or (d38, d21, d32);
	or (d39, d21, d40);
	or (d40, d8, d13);
	assign f2 = d41;
	and (d41, d2, d42);
	and (d42, d6, d43);
	and (d43, d20, d44);
	and (d44, d23, d45);
	and (d45, d39, d46);
	or (d46, d12, d21);
	assign f3 = d47;
	and (d47, d31, d48);
	and (d48, d6, d49);
	and (d49, d50, d51);
	or (d50, x0, d24);
	and (d51, d52, d53);
	or (d52, x0, d40);
	and (d53, d36, d54);
	and (d54, d55, d56);
	or (d55, d7, d21);
	and (d56, d27, d57);
	and (d57, d28, d39);
endmodule
