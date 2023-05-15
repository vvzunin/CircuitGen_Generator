//f0 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f2 = (x0 or not x1 or not x2)
//f3 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT1097_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, d4, d8);
	not (d8, x1);
	and (d9, d10, d12);
	or (d10, d3, d11);
	not (d11, x0);
	or (d12, d7, d11);
	assign f1 = d13;
	and (d13, d14, d16);
	or (d14, x0, d15);
	or (d15, x1, x2);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, x2, d8);
	and (d19, d6, d20);
	and (d20, d21, d22);
	or (d21, d11, d15);
	and (d22, d10, d23);
	or (d23, d11, d18);
	assign f2 = d6;
	assign f3 = d24;
	and (d24, d2, d25);
	and (d25, d17, d26);
	and (d26, d12, d23);
	assign f4 = d27;
	and (d27, d14, d28);
	and (d28, d6, d29);
	and (d29, d10, d26);
endmodule
