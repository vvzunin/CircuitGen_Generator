//f0 = (x0 or x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or not x1 or x2) and (not x0 or x1 or not x2)
//f3 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f5 = (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2)
//f6 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
module CCGRTT1280_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	and (d5, d6, d8);
	or (d6, d3, d7);
	not (d7, x0);
	or (d8, d7, d9);
	or (d9, d4, d10);
	not (d10, x1);
	assign f1 = d11;
	and (d11, d12, d14);
	or (d12, x0, d13);
	or (d13, x1, x2);
	and (d14, d15, d17);
	or (d15, x0, d16);
	or (d16, x2, d10);
	and (d17, d18, d19);
	or (d18, x0, d9);
	and (d19, d20, d21);
	or (d20, d7, d13);
	and (d21, d6, d22);
	and (d22, d8, d23);
	or (d23, d7, d16);
	assign f2 = d24;
	and (d24, d6, d15);
	assign f3 = d25;
	and (d25, d12, d26);
	and (d26, d2, d27);
	and (d27, d20, d28);
	and (d28, d6, d23);
	assign f4 = d29;
	and (d29, d12, d30);
	and (d30, d15, d31);
	and (d31, d20, d22);
	assign f5 = d32;
	and (d32, d15, d33);
	and (d33, d18, d34);
	and (d34, d20, d23);
	assign f6 = d35;
	and (d35, d2, d36);
	and (d36, d15, d37);
	and (d37, d18, d28);
endmodule
