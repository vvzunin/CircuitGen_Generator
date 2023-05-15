//f0 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2)
//f1 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2)
//f2 = (x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f4 = (x0 or not x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f5 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f6 = (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f7 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT1384_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d8);
	or (d5, x0, d6);
	or (d6, x1, d7);
	not (d7, x2);
	and (d8, d9, d12);
	or (d9, x0, d10);
	or (d10, d7, d11);
	not (d11, x1);
	or (d12, d3, d13);
	not (d13, x0);
	assign f1 = d14;
	and (d14, d2, d15);
	and (d15, d5, d16);
	or (d16, x0, d17);
	or (d17, x2, d11);
	assign f2 = d18;
	and (d18, d2, d19);
	and (d19, d20, d21);
	or (d20, d6, d13);
	or (d21, d10, d13);
	assign f3 = d22;
	and (d22, d2, d23);
	and (d23, d5, d24);
	and (d24, d16, d25);
	and (d25, d9, d26);
	and (d26, d12, d20);
	assign f4 = d27;
	and (d27, d16, d28);
	and (d28, d20, d29);
	and (d29, d21, d30);
	or (d30, d13, d17);
	assign f5 = d31;
	and (d31, d2, d32);
	and (d32, d5, d33);
	and (d33, d16, d34);
	and (d34, d12, d21);
	assign f6 = d35;
	and (d35, d12, d36);
	and (d36, d20, d30);
	assign f7 = d37;
	and (d37, d2, d38);
	and (d38, d5, d39);
	and (d39, d9, d28);
endmodule
