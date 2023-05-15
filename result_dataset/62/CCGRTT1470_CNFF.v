//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1470_CNFF(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42;

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
	and (d14, d15, d17);
	or (d15, d3, d16);
	not (d16, x0);
	and (d17, d18, d22);
	or (d18, d16, d19);
	or (d19, x1, d20);
	or (d20, x2, d21);
	not (d21, x3);
	and (d22, d23, d26);
	or (d23, d16, d24);
	or (d24, x1, d25);
	or (d25, d9, d21);
	and (d26, d27, d29);
	or (d27, d16, d28);
	or (d28, d8, d13);
	or (d29, d16, d30);
	or (d30, d13, d25);
	assign f1 = d31;
	and (d31, d2, d32);
	and (d32, d6, d33);
	and (d33, d11, d34);
	and (d34, d35, d36);
	or (d35, x0, d28);
	and (d36, d15, d37);
	and (d37, d18, d38);
	and (d38, d39, d40);
	or (d39, d12, d16);
	and (d40, d27, d41);
	or (d41, d16, d42);
	or (d42, d13, d20);
endmodule
