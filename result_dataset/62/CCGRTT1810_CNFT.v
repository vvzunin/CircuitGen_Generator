//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1810_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	or (d12, d13, d15);
	and (d13, d3, d14);
	and (d14, x1, d6);
	or (d15, d16, d18);
	and (d16, d3, d17);
	and (d17, x1, d11);
	or (d18, d19, d23);
	and (d19, x0, d20);
	and (d20, d5, d21);
	and (d21, d7, d22);
	not (d22, x3);
	or (d23, d24, d25);
	and (d24, x0, d14);
	and (d25, x0, d26);
	and (d26, x1, d27);
	and (d27, x2, d22);
	assign f1 = d28;
	or (d28, d29, d30);
	and (d29, d3, d20);
	or (d30, d2, d31);
	or (d31, d9, d32);
	or (d32, d16, d33);
	or (d33, d23, d34);
	and (d34, x0, d4);
	assign f2 = d35;
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, d5, d27);
	or (d38, d9, d39);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, x1, d21);
	or (d42, d13, d43);
	or (d43, d44, d45);
	and (d44, x0, d37);
	or (d45, d25, d46);
	and (d46, x0, d10);
	assign f3 = d47;
	or (d47, d36, d48);
	or (d48, d13, d49);
	or (d49, d50, d51);
	and (d50, d3, d26);
	or (d51, d19, d52);
	or (d52, d34, d53);
	or (d53, d44, d54);
	or (d54, d24, d55);
	or (d55, d25, d56);
	and (d56, x0, d17);
	assign f4 = d57;
	or (d57, d36, d58);
	or (d58, d40, d59);
	or (d59, d13, d60);
	or (d60, d50, d55);
	assign f5 = d61;
	or (d61, d40, d62);
	or (d62, d13, d63);
	or (d63, d34, d64);
	or (d64, d25, d65);
	and (d65, x0, d41);
endmodule
