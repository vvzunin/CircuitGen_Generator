//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1433_CNFF(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43;

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
	or (d18, d9, d14);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d14, d22);
	or (d22, d5, d10);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d15);
	and (d27, d28, d29);
	or (d28, d3, d25);
	and (d29, d30, d31);
	or (d30, d8, d25);
	and (d31, d32, d34);
	or (d32, d25, d33);
	or (d33, x1, d22);
	or (d34, d25, d35);
	or (d35, d4, d14);
	assign f1 = d36;
	and (d36, d2, d37);
	and (d37, d7, d38);
	and (d38, d12, d39);
	and (d39, d17, d40);
	and (d40, d20, d41);
	and (d41, d28, d42);
	and (d42, d30, d43);
	or (d43, d18, d25);
endmodule
