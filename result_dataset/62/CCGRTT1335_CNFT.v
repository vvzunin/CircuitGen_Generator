//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2)
//f1 = (not x0 and not x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
//f2 = (not x0 and x1 and x2) or (x0 and x1 and not x2)
//f3 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
//f4 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and not x1 and x2)
//f5 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
//f6 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
//f7 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and x1 and x2)
module CCGRTT1335_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	and (d6, d3, d7);
	and (d7, x1, d8);
	not (d8, x2);
	assign f1 = d9;
	or (d9, d2, d10);
	or (d10, d11, d13);
	and (d11, x0, d12);
	and (d12, d5, d8);
	or (d13, d14, d15);
	and (d14, x0, d4);
	and (d15, x0, d16);
	and (d16, x1, x2);
	assign f2 = d17;
	or (d17, d18, d19);
	and (d18, d3, d16);
	and (d19, x0, d7);
	assign f3 = d20;
	or (d20, d21, d22);
	and (d21, d3, d12);
	or (d22, d2, d23);
	or (d23, d18, d24);
	or (d24, d14, d19);
	assign f4 = d25;
	or (d25, d2, d26);
	or (d26, d6, d14);
	assign f5 = d27;
	or (d27, d21, d28);
	or (d28, d6, d29);
	or (d29, d13, d18);
	assign f6 = d20;
	assign f7 = d30;
	or (d30, d21, d31);
	or (d31, d2, d32);
	or (d32, d6, d15);
endmodule
