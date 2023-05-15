//f0 = (not x0 and x1 and x2) or (x0 and x1 and not x2)
//f1 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f4 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
module CCGRTT1021_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29;

	assign f0 = d1;
	or (d1, d2, d5);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, x2);
	and (d5, x0, d6);
	and (d6, x1, d7);
	not (d7, x2);
	assign f1 = d8;
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d7, d11);
	not (d11, x1);
	or (d12, d13, d15);
	and (d13, d3, d14);
	and (d14, x2, d11);
	or (d15, d16, d17);
	and (d16, d3, d6);
	or (d17, d2, d18);
	or (d18, d19, d20);
	and (d19, x0, d14);
	or (d20, d5, d21);
	and (d21, x0, d4);
	assign f2 = d22;
	or (d22, d9, d23);
	or (d23, d2, d24);
	or (d24, d20, d25);
	and (d25, x0, d10);
	assign f3 = d26;
	or (d26, d9, d27);
	or (d27, d2, d28);
	or (d28, d5, d25);
	assign f4 = d29;
	or (d29, d13, d23);
endmodule
