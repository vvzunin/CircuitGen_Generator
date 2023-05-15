//f0 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or not x1 or x2)
//f1 = (not x0 or x1 or x2)
//f2 = (x0 or x1 or not x2)
//f3 = (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
module CCGRTT329_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, x2, d8);
	not (d8, x1);
	and (d9, d10, d12);
	or (d10, x0, d11);
	or (d11, d4, d8);
	or (d12, d7, d13);
	not (d13, x0);
	assign f1 = d14;
	or (d14, d13, d15);
	or (d15, x1, x2);
	assign f2 = d2;
	assign f3 = d16;
	and (d16, d2, d17);
	and (d17, d12, d14);
	assign f4 = d18;
	and (d18, d19, d20);
	or (d19, x0, d15);
	and (d20, d6, d21);
	and (d21, d22, d23);
	or (d22, d3, d13);
	and (d23, d12, d24);
	or (d24, d11, d13);
endmodule
