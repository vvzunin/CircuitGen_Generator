//f0 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2)
//f1 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and x1 and not x2)
//f2 = (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and not x1 and not x2) or (x0 and not x1 and not x2)
//f4 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and x2)
//f5 = (not x0 and not x1 and not x2) or (not x0 and x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f6 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f7 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2)
module CCGRTT1361_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	not (d6, x2);
	or (d7, d8, d10);
	and (d8, d3, d9);
	and (d9, d5, x2);
	or (d10, d11, d13);
	and (d11, d3, d12);
	and (d12, x1, d6);
	and (d13, d3, d14);
	and (d14, x1, x2);
	assign f1 = d15;
	or (d15, d2, d16);
	or (d16, d8, d17);
	or (d17, d11, d18);
	and (d18, x0, d12);
	assign f2 = d19;
	or (d19, d11, d20);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d18, d23);
	and (d23, x0, d14);
	assign f3 = d24;
	or (d24, d2, d21);
	assign f4 = d25;
	or (d25, d2, d26);
	or (d26, d11, d27);
	or (d27, d21, d23);
	assign f5 = d28;
	or (d28, d2, d29);
	or (d29, d13, d22);
	assign f6 = d30;
	or (d30, d2, d31);
	or (d31, d11, d29);
	assign f7 = d32;
	or (d32, d2, d33);
	or (d33, d8, d34);
	or (d34, d11, d35);
	or (d35, d13, d21);
endmodule
