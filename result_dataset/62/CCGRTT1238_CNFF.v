//f0 = (x0 or x1 or x2) and (x0 or not x1 or x2)
//f1 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or not x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2)
//f4 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f5 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f6 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2)
module CCGRTT1238_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	or (d4, x0, d5);
	or (d5, x2, d6);
	not (d6, x1);
	assign f1 = d7;
	and (d7, d8, d11);
	or (d8, x0, d9);
	or (d9, x1, d10);
	not (d10, x2);
	and (d11, d4, d12);
	and (d12, d13, d15);
	or (d13, x0, d14);
	or (d14, d6, d10);
	and (d15, d16, d18);
	or (d16, d3, d17);
	not (d17, x0);
	and (d18, d19, d20);
	or (d19, d9, d17);
	or (d20, d14, d17);
	assign f2 = d21;
	and (d21, d4, d22);
	and (d22, d19, d23);
	and (d23, d20, d24);
	or (d24, d5, d17);
	assign f3 = d25;
	and (d25, d2, d26);
	and (d26, d13, d19);
	assign f4 = d27;
	and (d27, d8, d28);
	and (d28, d4, d23);
	assign f5 = d29;
	and (d29, d8, d30);
	and (d30, d4, d18);
	assign f6 = d31;
	and (d31, d8, d32);
	and (d32, d4, d33);
	and (d33, d13, d16);
endmodule
