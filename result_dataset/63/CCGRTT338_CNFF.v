//f0 = (not x0 or x1 or not x2)
//f1 = (x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or not x2) and (x0 or not x1 or x2)
//f3 = (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (not x0 or x1 or not x2)
//f5 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2)
module CCGRTT338_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26;

	assign f0 = d1;
	or (d1, d2, d3);
	not (d2, x0);
	or (d3, x1, d4);
	not (d4, x2);
	assign f1 = d5;
	and (d5, d6, d7);
	or (d6, x0, d3);
	or (d7, d2, d8);
	or (d8, d4, d9);
	not (d9, x1);
	assign f2 = d10;
	and (d10, d6, d11);
	or (d11, x0, d12);
	or (d12, x2, d9);
	assign f3 = d13;
	and (d13, d11, d14);
	and (d14, d15, d16);
	or (d15, x0, d8);
	and (d16, d1, d17);
	and (d17, d7, d18);
	or (d18, d2, d12);
	assign f4 = d19;
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, x1, x2);
	and (d22, d1, d6);
	assign f5 = d23;
	and (d23, d20, d24);
	and (d24, d15, d25);
	and (d25, d18, d26);
	or (d26, d2, d21);
endmodule
