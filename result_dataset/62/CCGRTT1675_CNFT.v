//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
module CCGRTT1675_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53;

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
	and (d11, x1, d12);
	and (d12, d7, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, d8);
	or (d17, d18, d20);
	and (d18, x0, d19);
	and (d19, d5, d16);
	or (d20, d21, d22);
	and (d21, x0, d11);
	or (d22, d23, d24);
	and (d23, x0, d15);
	and (d24, x0, d25);
	and (d25, x1, d26);
	and (d26, x2, x3);
	assign f1 = d27;
	or (d27, d2, d28);
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, d5, d26);
	or (d31, d32, d34);
	and (d32, d3, d33);
	and (d33, x1, d6);
	or (d34, d14, d35);
	or (d35, d36, d37);
	and (d36, d3, d25);
	or (d37, d38, d39);
	and (d38, x0, d4);
	or (d39, d40, d41);
	and (d40, x0, d30);
	and (d41, x0, d33);
	assign f2 = d42;
	or (d42, d2, d43);
	or (d43, d10, d44);
	or (d44, d36, d45);
	or (d45, d38, d46);
	or (d46, d23, d40);
	assign f3 = d47;
	or (d47, d48, d50);
	and (d48, d3, d49);
	and (d49, d5, d12);
	or (d50, d51, d52);
	and (d51, d3, d19);
	or (d52, d32, d53);
	or (d53, d14, d39);
endmodule
