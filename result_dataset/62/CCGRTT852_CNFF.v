//f0 = (x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f2 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
module CCGRTT852_CNFF(
	input x0, x1, x2,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	not (d4, x2);
	and (d5, d6, d10);
	or (d6, d7, d8);
	not (d7, x0);
	or (d8, x2, d9);
	not (d9, x1);
	or (d10, d7, d11);
	or (d11, d4, d9);
	assign f1 = d12;
	and (d12, d13, d15);
	or (d13, x0, d14);
	or (d14, x1, x2);
	and (d15, d16, d17);
	or (d16, x0, d11);
	and (d17, d10, d18);
	or (d18, d7, d14);
	assign f2 = d19;
	and (d19, d13, d20);
	and (d20, d2, d21);
	and (d21, d6, d22);
	or (d22, d3, d7);
endmodule
