//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f1 = (not x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2)
//f3 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f4 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2)
//f5 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f6 = (not x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
module CCGRTT1208_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	or (d6, d7, d9);
	and (d7, d3, d8);
	and (d8, x1, x2);
	or (d9, d10, d13);
	and (d10, x0, d11);
	and (d11, d5, d12);
	not (d12, x2);
	or (d13, d14, d15);
	and (d14, x0, d4);
	or (d15, d16, d18);
	and (d16, x0, d17);
	and (d17, x1, d12);
	and (d18, x0, d8);
	assign f1 = d19;
	or (d19, d16, d20);
	and (d20, d3, d11);
	assign f2 = d21;
	or (d21, d20, d22);
	or (d22, d2, d23);
	or (d23, d7, d10);
	assign f3 = d24;
	or (d24, d2, d25);
	or (d25, d26, d27);
	and (d26, d3, d17);
	or (d27, d10, d15);
	assign f4 = d28;
	or (d28, d20, d29);
	or (d29, d7, d30);
	or (d30, d10, d14);
	assign f5 = d31;
	or (d31, d20, d32);
	or (d32, d7, d33);
	or (d33, d10, d16);
	assign f6 = d34;
	or (d34, d13, d20);
endmodule
