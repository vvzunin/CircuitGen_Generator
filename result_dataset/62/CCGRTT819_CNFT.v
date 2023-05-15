//f0 = (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and x1 and x2)
//f1 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
//f2 = (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
module CCGRTT819_CNFT(
	input x0, x1, x2,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	not (d5, x2);
	or (d6, d7, d9);
	and (d7, d3, d8);
	and (d8, x1, x2);
	and (d9, x0, d8);
	assign f1 = d10;
	or (d10, d11, d14);
	and (d11, d3, d12);
	and (d12, d5, d13);
	not (d13, x1);
	or (d14, d15, d17);
	and (d15, d3, d16);
	and (d16, x2, d13);
	or (d17, d2, d18);
	or (d18, d19, d20);
	and (d19, x0, d16);
	and (d20, x0, d4);
	assign f2 = d21;
	or (d21, d2, d22);
	or (d22, d7, d18);
endmodule
