//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and x2)
//f1 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f4 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2)
//f5 = (not x0 and not x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
module CCGRTT351_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	and (d6, d3, d7);
	and (d7, x1, x2);
	assign f1 = d8;
	or (d8, d2, d9);
	or (d9, d10, d13);
	and (d10, d3, d11);
	and (d11, x1, d12);
	not (d12, x2);
	or (d13, d6, d14);
	or (d14, d15, d16);
	and (d15, x0, d4);
	or (d16, d17, d18);
	and (d17, x0, d11);
	and (d18, x0, d7);
	assign f2 = d19;
	or (d19, d8, d20);
	and (d20, d3, d21);
	and (d21, d5, d12);
	assign f3 = d22;
	or (d22, d20, d23);
	or (d23, d2, d24);
	or (d24, d10, d25);
	or (d25, d14, d26);
	and (d26, x0, d21);
	assign f4 = d27;
	or (d27, d20, d28);
	or (d28, d2, d29);
	or (d29, d10, d30);
	or (d30, d6, d31);
	or (d31, d15, d26);
	assign f5 = d32;
	or (d32, d20, d33);
	or (d33, d16, d26);
endmodule
