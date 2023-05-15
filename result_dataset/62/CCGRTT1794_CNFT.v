//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1794_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d11);
	and (d9, d3, d10);
	and (d10, x1, d6);
	or (d11, d12, d15);
	and (d12, d3, d13);
	and (d13, x1, d14);
	and (d14, x2, x3);
	or (d15, d16, d20);
	and (d16, x0, d17);
	and (d17, d5, d18);
	and (d18, d7, d19);
	not (d19, x3);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, x2, d19);
	or (d24, d25, d26);
	and (d25, x0, d10);
	and (d26, x0, d27);
	and (d27, x1, d23);
	assign f1 = d28;
	or (d28, d2, d29);
	or (d29, d30, d31);
	and (d30, d3, d22);
	or (d31, d32, d34);
	and (d32, d3, d33);
	and (d33, d5, d14);
	or (d34, d35, d37);
	and (d35, d3, d36);
	and (d36, x1, d18);
	or (d37, d38, d39);
	and (d38, x0, d33);
	and (d39, x0, d36);
	assign f2 = d40;
	or (d40, d2, d41);
	or (d41, d30, d42);
	or (d42, d35, d43);
	or (d43, d44, d45);
	and (d44, d3, d27);
	or (d45, d12, d46);
	or (d46, d26, d38);
	assign f3 = d47;
	or (d47, d48, d49);
	and (d48, d3, d17);
	or (d49, d30, d50);
	or (d50, d35, d51);
	or (d51, d9, d52);
	or (d52, d44, d53);
	or (d53, d39, d54);
	or (d54, d25, d55);
	and (d55, x0, d13);
	assign f4 = d56;
	or (d56, d45, d48);
endmodule
