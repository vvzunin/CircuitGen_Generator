//f0 = (not x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1609_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d13);
	and (d9, x0, d10);
	and (d10, d5, d11);
	and (d11, x2, d12);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, x0, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d21);
	and (d18, x0, d19);
	and (d19, x1, d20);
	and (d20, d7, d12);
	and (d21, x0, d22);
	and (d22, x1, d16);
	assign f1 = d23;
	or (d23, d24, d26);
	and (d24, d3, d25);
	and (d25, d5, d20);
	or (d26, d2, d27);
	or (d27, d28, d29);
	and (d28, d3, d15);
	or (d29, d9, d30);
	and (d30, x0, d31);
	and (d31, x1, d6);
	assign f2 = d32;
	or (d32, d28, d33);
	or (d33, d34, d35);
	and (d34, x0, d25);
	or (d35, d14, d36);
	or (d36, d18, d37);
	or (d37, d30, d38);
	or (d38, d21, d39);
	and (d39, x0, d40);
	and (d40, x1, d11);
	assign f3 = d41;
	or (d41, d24, d42);
	or (d42, d2, d43);
	or (d43, d33, d44);
	and (d44, d3, d40);
endmodule
