//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1414_CNFF(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x2, d9);
	not (d9, x3);
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d20);
	or (d15, d16, d17);
	not (d16, x0);
	or (d17, x1, d18);
	or (d18, x3, d19);
	not (d19, x2);
	or (d20, d12, d16);
	assign f1 = d21;
	and (d21, d2, d22);
	and (d22, d6, d23);
	and (d23, d24, d25);
	or (d24, x0, d17);
	and (d25, d26, d29);
	or (d26, x0, d27);
	or (d27, x1, d28);
	or (d28, d9, d19);
	and (d29, d11, d30);
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, d8, d13);
	and (d33, d34, d36);
	or (d34, x0, d35);
	or (d35, d13, d18);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d13, d28);
	and (d39, d40, d41);
	or (d40, d3, d16);
	and (d41, d42, d43);
	or (d42, d7, d16);
	and (d43, d15, d44);
	and (d44, d45, d46);
	or (d45, d16, d32);
	or (d46, d16, d38);
endmodule
