//f0 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3)
module CCGRTT1862_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

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
	or (d12, d13, d16);
	and (d13, x0, d14);
	and (d14, d5, d15);
	not (d15, x1);
	or (d16, d17, d19);
	and (d17, x0, d18);
	and (d18, d10, d15);
	and (d19, x0, d20);
	and (d20, x1, d21);
	and (d21, d6, d11);
	assign f1 = d22;
	or (d22, d23, d24);
	and (d23, d3, d14);
	or (d24, d25, d26);
	and (d25, d3, d20);
	or (d26, d2, d27);
	or (d27, d28, d31);
	and (d28, d3, d29);
	and (d29, x1, d30);
	and (d30, x2, x3);
	or (d31, d32, d34);
	and (d32, x0, d33);
	and (d33, d15, d21);
	or (d34, d13, d35);
	or (d35, d36, d38);
	and (d36, x0, d37);
	and (d37, d15, d30);
	or (d38, d39, d40);
	and (d39, x0, d4);
	and (d40, x0, d29);
	assign f2 = d41;
	or (d41, d42, d43);
	and (d42, d3, d37);
	or (d43, d25, d44);
	or (d44, d2, d8);
	assign f3 = d45;
	or (d45, d46, d47);
	and (d46, d3, d33);
	and (d47, x0, d9);
	assign f4 = d48;
	or (d48, d46, d49);
	or (d49, d23, d50);
	or (d50, d51, d52);
	and (d51, d3, d18);
	or (d52, d42, d53);
	or (d53, d25, d54);
	or (d54, d2, d55);
	or (d55, d8, d56);
	or (d56, d28, d57);
	or (d57, d32, d58);
	or (d58, d39, d59);
	or (d59, d40, d47);
	assign f5 = d60;
	or (d60, d23, d61);
	or (d61, d2, d62);
	or (d62, d28, d36);
endmodule
