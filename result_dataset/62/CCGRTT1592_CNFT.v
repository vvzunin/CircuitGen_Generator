//f0 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1592_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	and (d5, d6, x3);
	not (d6, x2);
	or (d7, d8, d12);
	and (d8, d3, d9);
	and (d9, x1, d10);
	and (d10, x2, d11);
	not (d11, x3);
	or (d12, d13, d17);
	and (d13, x0, d14);
	and (d14, d15, d16);
	not (d15, x1);
	and (d16, d6, d11);
	or (d17, d18, d21);
	and (d18, x0, d19);
	and (d19, d15, d20);
	and (d20, x2, x3);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, x1, d16);
	or (d24, d25, d26);
	and (d25, x0, d4);
	and (d26, x0, d27);
	and (d27, x1, d20);
	assign f1 = d28;
	or (d28, d29, d30);
	and (d29, d3, d14);
	or (d30, d31, d32);
	and (d31, d3, d19);
	or (d32, d2, d33);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, d5, d15);
	and (d36, x0, d9);
	assign f2 = d37;
	or (d37, d38, d39);
	and (d38, d3, d35);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, d10, d15);
	or (d42, d31, d43);
	or (d43, d44, d45);
	and (d44, d3, d23);
	or (d45, d8, d46);
	or (d46, d47, d48);
	and (d47, d3, d27);
	or (d48, d24, d34);
endmodule
