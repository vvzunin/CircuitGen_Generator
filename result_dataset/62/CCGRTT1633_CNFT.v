//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1633_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	and (d15, d7, d16);
	not (d16, x2);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d11);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d5, d15);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, d5, d26);
	and (d26, x3, d16);
	or (d27, d28, d29);
	and (d28, x0, d4);
	or (d29, d30, d31);
	and (d30, x0, d10);
	or (d31, d32, d33);
	and (d32, x0, d14);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, x1, d26);
	or (d36, d37, d39);
	and (d37, x0, d38);
	and (d38, x1, d6);
	and (d39, x0, d19);
	assign f1 = d40;
	or (d40, d41, d42);
	and (d41, d3, d22);
	or (d42, d9, d43);
	or (d43, d44, d45);
	and (d44, d3, d35);
	or (d45, d46, d47);
	and (d46, d3, d38);
	or (d47, d24, d48);
	or (d48, d28, d49);
	or (d49, d32, d39);
	assign f2 = d50;
	or (d50, d41, d51);
	or (d51, d9, d52);
	or (d52, d13, d53);
	or (d53, d44, d54);
	or (d54, d21, d55);
	or (d55, d28, d56);
	or (d56, d30, d57);
	or (d57, d32, d58);
	or (d58, d34, d37);
	assign f3 = d59;
	or (d59, d60, d61);
	and (d60, d3, d25);
	or (d61, d2, d62);
	or (d62, d9, d63);
	or (d63, d13, d64);
	or (d64, d46, d65);
	or (d65, d30, d36);
endmodule
