//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
module CCGRTT446_CNFT(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44;

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
	and (d14, x0, d15);
	and (d15, d5, d16);
	and (d16, x2, d8);
	and (d17, x0, d18);
	and (d18, x1, d12);
	assign f1 = d19;
	or (d19, d20, d23);
	and (d20, d3, d21);
	and (d21, d5, d22);
	and (d22, d7, x3);
	or (d23, d24, d25);
	and (d24, d3, d15);
	or (d25, d10, d26);
	or (d26, d27, d29);
	and (d27, d3, d28);
	and (d28, x1, d6);
	or (d29, d30, d32);
	and (d30, d3, d31);
	and (d31, x1, d22);
	or (d32, d33, d35);
	and (d33, d3, d34);
	and (d34, x1, d16);
	or (d35, d36, d37);
	and (d36, x0, d4);
	or (d37, d38, d39);
	and (d38, x0, d21);
	or (d39, d14, d40);
	or (d40, d41, d42);
	and (d41, x0, d11);
	or (d42, d43, d44);
	and (d43, x0, d28);
	and (d44, x0, d31);
endmodule
