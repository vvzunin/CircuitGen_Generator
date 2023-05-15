//f0 = (not x0 and x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f1 = (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f3 = (x0 and x1 and not x2) or (x0 and x1 and x2)
//f4 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2)
//f5 = (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
//f6 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and x1 and x2)
//f7 = (not x0 and x1 and not x2) or (x0 and not x1 and not x2)
module CCGRTT1390_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	not (d5, x2);
	or (d6, d7, d10);
	and (d7, x0, d8);
	and (d8, x2, d9);
	not (d9, x1);
	or (d10, d11, d12);
	and (d11, x0, d4);
	and (d12, x0, d13);
	and (d13, x1, x2);
	assign f1 = d14;
	or (d14, d15, d16);
	and (d15, d3, d13);
	or (d16, d6, d17);
	and (d17, x0, d18);
	and (d18, d5, d9);
	assign f2 = d19;
	or (d19, d20, d21);
	and (d20, d3, d8);
	or (d21, d2, d22);
	or (d22, d15, d23);
	or (d23, d11, d17);
	assign f3 = d10;
	assign f4 = d24;
	or (d24, d25, d26);
	and (d25, d3, d18);
	or (d26, d20, d27);
	or (d27, d15, d17);
	assign f5 = d28;
	or (d28, d15, d29);
	or (d29, d7, d11);
	assign f6 = d30;
	or (d30, d25, d31);
	or (d31, d20, d32);
	or (d32, d2, d33);
	or (d33, d12, d15);
	assign f7 = d34;
	or (d34, d2, d17);
endmodule
