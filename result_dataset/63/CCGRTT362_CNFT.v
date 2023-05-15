//f0 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and x2)
//f1 = (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f3 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f4 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2)
//f5 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2)
//f6 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and not x1 and x2) or (x0 and x1 and x2)
module CCGRTT362_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42;

	assign f0 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	or (d6, d7, d10);
	and (d7, d3, d8);
	and (d8, x1, d9);
	not (d9, x2);
	or (d10, d11, d13);
	and (d11, x0, d12);
	and (d12, d5, d9);
	and (d13, x0, d14);
	and (d14, x1, x2);
	assign f1 = d15;
	or (d15, d2, d16);
	or (d16, d7, d17);
	or (d17, d18, d19);
	and (d18, d3, d14);
	or (d19, d11, d20);
	or (d20, d13, d21);
	and (d21, x0, d8);
	assign f2 = d22;
	or (d22, d23, d24);
	and (d23, d3, d12);
	or (d24, d2, d25);
	or (d25, d7, d26);
	or (d26, d20, d27);
	and (d27, x0, d4);
	assign f3 = d28;
	or (d28, d23, d29);
	or (d29, d2, d30);
	or (d30, d11, d26);
	assign f4 = d31;
	or (d31, d23, d32);
	or (d32, d7, d33);
	or (d33, d11, d27);
	assign f5 = d34;
	or (d34, d23, d35);
	or (d35, d7, d36);
	or (d36, d11, d21);
	assign f6 = d37;
	or (d37, d23, d38);
	or (d38, d2, d39);
	or (d39, d7, d40);
	or (d40, d18, d41);
	or (d41, d11, d42);
	or (d42, d13, d27);
endmodule
