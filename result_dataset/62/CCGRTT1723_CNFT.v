//f0 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1723_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

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
	and (d16, x2, d12);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, x3, d11);
	or (d24, d25, d26);
	and (d25, x0, d4);
	and (d26, x0, d19);
	assign f1 = d27;
	or (d27, d28, d30);
	and (d28, d3, d29);
	and (d29, x1, d23);
	or (d30, d14, d31);
	or (d31, d21, d32);
	or (d32, d26, d33);
	and (d33, x0, d34);
	and (d34, d5, d16);
	assign f2 = d35;
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, d5, d10);
	or (d38, d8, d39);
	or (d39, d28, d40);
	or (d40, d18, d41);
	or (d41, d33, d42);
	or (d42, d25, d43);
	or (d43, d44, d45);
	and (d44, x0, d9);
	or (d45, d46, d47);
	and (d46, x0, d29);
	and (d47, x0, d15);
	assign f3 = d48;
	or (d48, d36, d49);
	or (d49, d50, d51);
	and (d50, d3, d34);
	or (d51, d2, d52);
	or (d52, d28, d53);
	or (d53, d47, d54);
	and (d54, x0, d37);
	assign f4 = d55;
	or (d55, d56, d57);
	and (d56, d3, d22);
	or (d57, d2, d58);
	or (d58, d8, d59);
	or (d59, d28, d60);
	or (d60, d54, d61);
	or (d61, d21, d62);
	or (d62, d33, d43);
endmodule
