//f0 = (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2)
//f3 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f5 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f6 = (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f7 = (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT1361_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, d3, d4);
	not (d3, x0);
	or (d4, x1, x2);
	and (d5, d6, d9);
	or (d6, d3, d7);
	or (d7, x1, d8);
	not (d8, x2);
	and (d9, d10, d13);
	or (d10, d3, d11);
	or (d11, x2, d12);
	not (d12, x1);
	or (d13, d3, d14);
	or (d14, d8, d12);
	assign f1 = d15;
	and (d15, d16, d17);
	or (d16, x0, d14);
	and (d17, d2, d18);
	and (d18, d6, d13);
	assign f2 = d19;
	and (d19, d20, d21);
	or (d20, x0, d4);
	and (d21, d22, d23);
	or (d22, x0, d7);
	and (d23, d6, d16);
	assign f3 = d24;
	and (d24, d22, d25);
	and (d25, d26, d27);
	or (d26, x0, d11);
	and (d27, d5, d16);
	assign f4 = d28;
	and (d28, d22, d29);
	and (d29, d16, d30);
	and (d30, d6, d10);
	assign f5 = d31;
	and (d31, d22, d32);
	and (d32, d26, d33);
	and (d33, d2, d6);
	assign f6 = d34;
	and (d34, d22, d33);
	assign f7 = d5;
endmodule
