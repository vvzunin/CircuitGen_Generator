//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT434_CNFF(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44;

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
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d14);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d9, d14);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, d14, d25);
	or (d25, d5, d10);
	and (d26, d27, d30);
	or (d27, d28, d29);
	not (d28, x0);
	or (d29, x1, d15);
	and (d30, d31, d32);
	or (d31, d3, d28);
	and (d32, d33, d35);
	or (d33, d28, d34);
	or (d34, x1, d25);
	and (d35, d36, d37);
	or (d36, d13, d28);
	and (d37, d38, d39);
	or (d38, d18, d28);
	or (d39, d21, d28);
	assign f1 = d40;
	and (d40, d41, d42);
	or (d41, x0, d29);
	and (d42, d23, d43);
	and (d43, d39, d44);
	or (d44, d24, d28);
endmodule
