//f0 = (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2)
//f2 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
//f3 = (x0 or x1 or x2) and (not x0 or not x1 or x2)
module CCGRTT997_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, d3, d4);
	not (d3, x0);
	or (d4, x1, d5);
	not (d5, x2);
	and (d6, d7, d10);
	or (d7, d3, d8);
	or (d8, x2, d9);
	not (d9, x1);
	or (d10, d3, d11);
	or (d11, d5, d9);
	assign f1 = d12;
	and (d12, d13, d15);
	or (d13, x0, d14);
	or (d14, x1, x2);
	and (d15, d16, d17);
	or (d16, x0, d4);
	and (d17, d18, d19);
	or (d18, x0, d11);
	and (d19, d2, d20);
	or (d20, d3, d14);
	assign f2 = d21;
	and (d21, d13, d22);
	and (d22, d23, d24);
	or (d23, x0, d8);
	and (d24, d20, d25);
	and (d25, d2, d7);
	assign f3 = d26;
	and (d26, d7, d13);
endmodule
