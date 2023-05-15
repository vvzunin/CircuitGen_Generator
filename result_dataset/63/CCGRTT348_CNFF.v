//f0 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (not x0 or x1 or x2)
//f2 = (not x0 or x1 or x2)
//f3 = (x0 or not x1 or not x2)
//f4 = (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f5 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or not x2)
module CCGRTT348_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d8);
	or (d5, x0, d6);
	or (d6, x2, d7);
	not (d7, x1);
	and (d8, d9, d11);
	or (d9, d3, d10);
	not (d10, x0);
	and (d11, d12, d15);
	or (d12, d10, d13);
	or (d13, x1, d14);
	not (d14, x2);
	and (d15, d16, d17);
	or (d16, d6, d10);
	or (d17, d10, d18);
	or (d18, d7, d14);
	assign f1 = d19;
	and (d19, d2, d9);
	assign f2 = d9;
	assign f3 = d20;
	or (d20, x0, d18);
	assign f4 = d15;
	assign f5 = d21;
	and (d21, d22, d23);
	or (d22, x0, d13);
	and (d23, d5, d24);
	and (d24, d12, d20);
endmodule
