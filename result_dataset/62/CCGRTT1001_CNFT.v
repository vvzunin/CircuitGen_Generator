//f0 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f1 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and not x1 and x2) or (x0 and not x1 and not x2)
//f4 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
module CCGRTT1001_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	not (d6, x2);
	or (d7, d8, d10);
	and (d8, d3, d9);
	and (d9, x1, x2);
	or (d10, d11, d13);
	and (d11, x0, d12);
	and (d12, d5, x2);
	or (d13, d14, d16);
	and (d14, x0, d15);
	and (d15, x1, d6);
	and (d16, x0, d9);
	assign f1 = d17;
	or (d17, d18, d19);
	and (d18, d3, d12);
	or (d19, d20, d21);
	and (d20, d3, d15);
	or (d21, d8, d13);
	assign f2 = d22;
	or (d22, d18, d23);
	or (d23, d13, d20);
	assign f3 = d24;
	or (d24, d18, d25);
	and (d25, x0, d4);
	assign f4 = d26;
	or (d26, d2, d27);
	or (d27, d18, d28);
	or (d28, d20, d29);
	or (d29, d8, d30);
	or (d30, d11, d16);
endmodule
