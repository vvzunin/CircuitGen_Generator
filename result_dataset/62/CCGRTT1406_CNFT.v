//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1406_CNFT(
	input x0, x1, x2, x3,
	output f0, f1
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, x3);
	or (d12, d13, d17);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, x3, d16);
	not (d16, x2);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d11);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, d5, d26);
	and (d26, d7, d16);
	or (d27, d28, d30);
	and (d28, x0, d29);
	and (d29, d5, d15);
	or (d30, d31, d32);
	and (d31, x0, d10);
	or (d32, d33, d34);
	and (d33, x0, d14);
	or (d34, d35, d36);
	and (d35, x0, d19);
	and (d36, x0, d22);
	assign f1 = d37;
	or (d37, d31, d38);
	or (d38, d35, d39);
	and (d39, x0, d40);
	and (d40, x1, d26);
endmodule
