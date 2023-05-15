//f0 = (not x0 and not x1 and not x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
//f1 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
//f4 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2)
module CCGRTT313_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	not (d6, x2);
	or (d7, d8, d9);
	and (d8, x0, d4);
	or (d9, d10, d12);
	and (d10, x0, d11);
	and (d11, d5, x2);
	and (d12, x0, d13);
	and (d13, x1, x2);
	assign f1 = d14;
	or (d14, d2, d15);
	or (d15, d16, d17);
	and (d16, d3, d11);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d22);
	and (d21, d3, d13);
	or (d22, d10, d23);
	or (d23, d12, d24);
	and (d24, x0, d19);
	assign f2 = d25;
	or (d25, d2, d26);
	or (d26, d18, d27);
	or (d27, d21, d28);
	or (d28, d8, d22);
	assign f3 = d29;
	or (d29, d2, d30);
	or (d30, d18, d31);
	or (d31, d9, d21);
	assign f4 = d32;
	or (d32, d16, d33);
	or (d33, d8, d21);
endmodule
