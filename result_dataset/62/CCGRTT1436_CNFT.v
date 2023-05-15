//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1436_CNFT(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d13);
	and (d10, d3, d11);
	and (d11, d5, d12);
	and (d12, x2, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, d7, x3);
	or (d17, d18, d20);
	and (d18, x0, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, x1, d23);
	and (d23, x2, d8);
	and (d24, x0, d25);
	and (d25, x1, d12);
	assign f1 = d26;
	or (d26, d2, d27);
	or (d27, d10, d28);
	or (d28, d14, d29);
	or (d29, d30, d31);
	and (d30, x0, d4);
	or (d31, d32, d33);
	and (d32, x0, d11);
	or (d33, d18, d34);
	or (d34, d24, d35);
	and (d35, x0, d15);
endmodule
