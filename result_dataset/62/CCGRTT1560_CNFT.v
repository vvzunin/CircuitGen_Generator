//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3)
module CCGRTT1560_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d12);
	and (d10, d3, d11);
	and (d11, x1, d6);
	or (d12, d13, d16);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, x2, d8);
	and (d16, x0, d11);
	assign f1 = d17;
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, d5, d15);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, d5, d23);
	and (d23, x2, x3);
	or (d24, d25, d28);
	and (d25, d3, d26);
	and (d26, x1, d27);
	and (d27, d7, x3);
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, x1, d23);
	or (d31, d32, d33);
	and (d32, x0, d4);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, d5, d27);
	or (d36, d37, d38);
	and (d37, x0, d22);
	and (d38, x0, d26);
	assign f2 = d39;
	or (d39, d2, d40);
	or (d40, d41, d42);
	and (d41, d3, d35);
	or (d42, d18, d43);
	or (d43, d21, d44);
	or (d44, d25, d45);
	or (d45, d13, d46);
	or (d46, d29, d47);
	or (d47, d32, d48);
	or (d48, d34, d37);
endmodule
