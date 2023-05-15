//f0 = (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2)
//f1 = (x0 or x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or not x1 or x2)
//f3 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2)
//f5 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f6 = (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f7 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2)
module CCGRTT1304_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, d4, x2);
	not (d4, x1);
	and (d5, d6, d9);
	or (d6, d7, d8);
	not (d7, x0);
	or (d8, x1, x2);
	or (d9, d3, d7);
	assign f1 = d10;
	and (d10, d11, d12);
	or (d11, x0, d8);
	and (d12, d6, d13);
	and (d13, d14, d17);
	or (d14, d7, d15);
	or (d15, x1, d16);
	not (d16, x2);
	and (d17, d9, d18);
	or (d18, d7, d19);
	or (d19, d4, d16);
	assign f2 = d20;
	and (d20, d21, d22);
	or (d21, x0, d15);
	and (d22, d2, d23);
	and (d23, d9, d24);
	or (d24, x0, d19);
	assign f3 = d25;
	and (d25, d11, d26);
	and (d26, d2, d27);
	and (d27, d24, d28);
	and (d28, d6, d14);
	assign f4 = d29;
	and (d29, d11, d30);
	and (d30, d2, d6);
	assign f5 = d31;
	and (d31, d21, d32);
	and (d32, d12, d24);
	assign f6 = d33;
	and (d33, d2, d34);
	and (d34, d6, d35);
	and (d35, d14, d18);
	assign f7 = d36;
	and (d36, d11, d37);
	and (d37, d21, d38);
	and (d38, d14, d24);
endmodule
