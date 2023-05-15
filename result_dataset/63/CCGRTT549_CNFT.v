//f0 = (not x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT549_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d10, x0, d11);
	and (d11, d5, d12);
	and (d12, x2, d8);
	or (d13, d14, d17);
	and (d14, x0, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, x0, d19);
	and (d19, x1, d6);
	and (d20, x0, d21);
	and (d21, x1, d16);
	assign f1 = d22;
	or (d22, d2, d23);
	or (d23, d24, d25);
	and (d24, x0, d4);
	or (d25, d14, d18);
	assign f2 = d26;
	or (d26, d2, d27);
	or (d27, d28, d29);
	and (d28, d3, d11);
	or (d29, d30, d31);
	and (d30, d3, d15);
	or (d31, d32, d33);
	and (d32, d3, d19);
	or (d33, d34, d37);
	and (d34, d3, d35);
	and (d35, x1, d36);
	and (d36, d7, x3);
	or (d37, d38, d40);
	and (d38, d3, d39);
	and (d39, x1, d12);
	or (d40, d41, d42);
	and (d41, d3, d21);
	or (d42, d24, d43);
	or (d43, d44, d46);
	and (d44, x0, d45);
	and (d45, d5, d36);
	or (d46, d10, d47);
	or (d47, d14, d48);
	and (d48, x0, d35);
	assign f3 = d49;
	or (d49, d2, d50);
	or (d50, d28, d51);
	or (d51, d34, d52);
	or (d52, d41, d53);
	or (d53, d14, d54);
	and (d54, x0, d39);
	assign f4 = d55;
	or (d55, d56, d57);
	and (d56, d3, d45);
	or (d57, d28, d58);
	or (d58, d34, d59);
	or (d59, d38, d60);
	or (d60, d24, d61);
	or (d61, d18, d54);
	assign f5 = d62;
	or (d62, d28, d63);
	or (d63, d41, d64);
	or (d64, d24, d65);
	or (d65, d44, d66);
	or (d66, d48, d54);
endmodule
