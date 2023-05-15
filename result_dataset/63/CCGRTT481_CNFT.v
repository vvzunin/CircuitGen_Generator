//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
module CCGRTT481_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

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
	and (d15, x2, d16);
	not (d16, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d11);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d23, d25);
	and (d23, x0, d24);
	and (d24, d5, d15);
	or (d25, d26, d29);
	and (d26, x0, d27);
	and (d27, x1, d28);
	and (d28, d7, d16);
	and (d29, x0, d14);
	assign f1 = d30;
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d28);
	or (d33, d34, d35);
	and (d34, d3, d24);
	or (d35, d9, d36);
	or (d36, d13, d37);
	or (d37, d38, d39);
	and (d38, x0, d32);
	or (d39, d23, d40);
	or (d40, d41, d42);
	and (d41, x0, d10);
	or (d42, d26, d43);
	or (d43, d44, d46);
	and (d44, x0, d45);
	and (d45, x1, d6);
	and (d46, x0, d19);
	assign f2 = d47;
	or (d47, d2, d48);
	or (d48, d9, d49);
	or (d49, d50, d51);
	and (d50, d3, d27);
	or (d51, d52, d53);
	and (d52, d3, d45);
	or (d53, d13, d54);
	or (d54, d18, d55);
	or (d55, d21, d56);
	or (d56, d23, d43);
	assign f3 = d57;
	or (d57, d31, d58);
	or (d58, d50, d59);
	or (d59, d52, d60);
	or (d60, d38, d61);
	or (d61, d21, d62);
	or (d62, d26, d41);
endmodule
