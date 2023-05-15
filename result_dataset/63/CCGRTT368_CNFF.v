//f0 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f1 = (x0 or x1 or x2) and (not x0 or x1 or not x2)
//f2 = (x0 or not x1 or not x2) and (not x0 or x1 or x2)
//f3 = (x0 or not x1 or x2) and (x0 or not x1 or not x2)
//f4 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f5 = (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f6 = (not x0 or not x1 or x2)
module CCGRTT368_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d9);
	or (d5, x0, d6);
	or (d6, d7, d8);
	not (d7, x1);
	not (d8, x2);
	and (d9, d10, d13);
	or (d10, d11, d12);
	not (d11, x0);
	or (d12, x1, d8);
	or (d13, d11, d14);
	or (d14, x2, d7);
	assign f1 = d15;
	and (d15, d2, d10);
	assign f2 = d16;
	and (d16, d5, d17);
	or (d17, d3, d11);
	assign f3 = d18;
	and (d18, d5, d19);
	or (d19, x0, d14);
	assign f4 = d20;
	and (d20, d21, d22);
	or (d21, x0, d12);
	and (d22, d5, d23);
	and (d23, d13, d24);
	or (d24, d6, d11);
	assign f5 = d25;
	and (d25, d21, d26);
	and (d26, d5, d27);
	and (d27, d10, d24);
	assign f6 = d13;
endmodule
