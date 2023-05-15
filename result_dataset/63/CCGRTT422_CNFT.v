//f0 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT422_CNFT(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, x3);
	or (d7, d8, d13);
	and (d8, d3, d9);
	and (d9, x1, d10);
	and (d10, d11, d12);
	not (d11, x2);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x3, d11);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d22);
	and (d21, x0, d9);
	or (d22, d23, d24);
	and (d23, x0, d15);
	and (d24, x0, d19);
	assign f1 = d25;
	or (d25, d26, d29);
	and (d26, d3, d27);
	and (d27, d5, d28);
	and (d28, x2, d12);
	or (d29, d8, d30);
	or (d30, d14, d31);
	or (d31, d32, d34);
	and (d32, d3, d33);
	and (d33, x1, d28);
	or (d34, d18, d35);
	or (d35, d36, d38);
	and (d36, x0, d37);
	and (d37, d5, d16);
	or (d38, d39, d40);
	and (d39, x0, d27);
	or (d40, d41, d42);
	and (d41, x0, d4);
	or (d42, d21, d43);
	or (d43, d23, d44);
	or (d44, d24, d45);
	and (d45, x0, d33);
endmodule
