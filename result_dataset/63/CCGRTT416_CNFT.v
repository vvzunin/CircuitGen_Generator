//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2)
//f1 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2)
//f2 = (not x0 and not x1 and x2) or (not x0 and x1 and x2)
//f3 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
//f4 = (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f5 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
//f6 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
//f7 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2)
module CCGRTT416_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
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
	and (d13, x0, d4);
	assign f1 = d1;
	assign f2 = d14;
	or (d14, d2, d7);
	assign f3 = d15;
	or (d15, d2, d16);
	or (d16, d17, d19);
	and (d17, d3, d18);
	and (d18, x1, d12);
	or (d19, d7, d20);
	or (d20, d10, d21);
	or (d21, d13, d22);
	and (d22, x0, d8);
	assign f4 = d23;
	or (d23, d10, d24);
	and (d24, x0, d18);
	assign f5 = d25;
	or (d25, d26, d27);
	and (d26, d3, d11);
	or (d27, d2, d28);
	or (d28, d17, d29);
	or (d29, d7, d30);
	or (d30, d13, d24);
	assign f6 = d31;
	or (d31, d26, d32);
	or (d32, d2, d33);
	or (d33, d7, d34);
	or (d34, d10, d30);
	assign f7 = d27;
endmodule
