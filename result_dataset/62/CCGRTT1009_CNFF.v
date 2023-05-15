//f0 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2)
//f1 = (x0 or x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f2 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f3 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (not x0 or x1 or x2) and (not x0 or not x1 or x2)
module CCGRTT1009_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, x2, d8);
	not (d8, x1);
	or (d9, d10, d11);
	not (d10, x0);
	or (d11, x1, x2);
	assign f1 = d12;
	and (d12, d13, d14);
	or (d13, x0, d11);
	and (d14, d9, d15);
	or (d15, d3, d10);
	assign f2 = d16;
	and (d16, d13, d17);
	and (d17, d14, d18);
	or (d18, x0, d19);
	or (d19, d4, d8);
	assign f3 = d20;
	and (d20, d13, d21);
	and (d21, d6, d22);
	and (d22, d18, d23);
	and (d23, d15, d24);
	and (d24, d25, d26);
	or (d25, d7, d10);
	or (d26, d10, d19);
	assign f4 = d27;
	and (d27, d9, d25);
endmodule
