//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
module CCGRTT1798_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, x3);
	or (d12, d13, d17);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, d7, d16);
	not (d16, x3);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, x2, d16);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, d5, d20);
	and (d24, x0, d25);
	and (d25, x1, d11);
	assign f1 = d26;
	or (d26, d27, d29);
	and (d27, d3, d28);
	and (d28, d5, d15);
	or (d29, d2, d30);
	or (d30, d9, d31);
	or (d31, d13, d32);
	or (d32, d33, d35);
	and (d33, d3, d34);
	and (d34, x1, d6);
	or (d35, d18, d36);
	or (d36, d37, d38);
	and (d37, x0, d4);
	or (d38, d22, d39);
	or (d39, d40, d41);
	and (d40, x0, d34);
	and (d41, x0, d19);
	assign f2 = d42;
	or (d42, d27, d43);
	or (d43, d44, d45);
	and (d44, d3, d23);
	or (d45, d46, d47);
	and (d46, d3, d25);
	or (d47, d22, d48);
	or (d48, d49, d50);
	and (d49, x0, d10);
	or (d50, d51, d52);
	and (d51, x0, d14);
	or (d52, d24, d41);
	assign f3 = d53;
	or (d53, d2, d54);
	or (d54, d44, d55);
	or (d55, d9, d56);
	or (d56, d18, d57);
	or (d57, d58, d59);
	and (d58, x0, d28);
	or (d59, d22, d40);
	assign f4 = d60;
	or (d60, d44, d61);
	or (d61, d22, d49);
endmodule
