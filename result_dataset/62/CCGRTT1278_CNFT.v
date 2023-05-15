//f0 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f1 = (not x0 and not x1 and x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and x1 and x2)
//f4 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2)
//f5 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
//f6 = (not x0 and not x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and x2)
module CCGRTT1278_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	not (d6, x2);
	or (d7, d8, d10);
	and (d8, d3, d9);
	and (d9, x1, d6);
	or (d10, d11, d13);
	and (d11, d3, d12);
	and (d12, x1, x2);
	or (d13, d14, d15);
	and (d14, x0, d4);
	and (d15, x0, d9);
	assign f1 = d16;
	and (d16, d3, d17);
	and (d17, d5, x2);
	assign f2 = d18;
	or (d18, d2, d19);
	or (d19, d16, d20);
	or (d20, d11, d21);
	or (d21, d14, d22);
	or (d22, d15, d23);
	and (d23, x0, d12);
	assign f3 = d24;
	or (d24, d8, d25);
	or (d25, d11, d23);
	assign f4 = d26;
	or (d26, d16, d27);
	or (d27, d11, d28);
	and (d28, x0, d17);
	assign f5 = d29;
	or (d29, d2, d30);
	or (d30, d16, d31);
	or (d31, d23, d28);
	assign f6 = d32;
	or (d32, d2, d33);
	or (d33, d14, d23);
endmodule
