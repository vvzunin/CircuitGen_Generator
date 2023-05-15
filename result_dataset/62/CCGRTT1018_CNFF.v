//f0 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f1 = (not x0 or x1 or x2)
//f2 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2)
//f3 = (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (not x0 or x1 or not x2)
module CCGRTT1018_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23;

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
	or (d10, x2, d11);
	not (d11, x1);
	and (d12, d13, d15);
	or (d13, d3, d14);
	not (d14, x0);
	and (d15, d16, d17);
	or (d16, d6, d14);
	or (d17, d14, d18);
	or (d18, d7, d11);
	assign f1 = d13;
	assign f2 = d19;
	and (d19, d5, d20);
	and (d20, d9, d16);
	assign f3 = d21;
	and (d21, d5, d22);
	and (d22, d9, d15);
	assign f4 = d23;
	and (d23, d2, d20);
endmodule
