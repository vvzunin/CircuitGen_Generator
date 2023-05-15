//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3)
module CCGRTT1842_CNFT(
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
	and (d10, d3, d11);
	and (d11, d5, d12);
	and (d12, x2, x3);
	or (d13, d14, d17);
	and (d14, x0, d15);
	and (d15, d5, d16);
	and (d16, x2, d8);
	or (d17, d18, d19);
	and (d18, x0, d11);
	or (d19, d20, d23);
	and (d20, x0, d21);
	and (d21, x1, d22);
	and (d22, d7, x3);
	and (d23, x0, d24);
	and (d24, x1, d16);
	assign f1 = d25;
	or (d25, d26, d28);
	and (d26, d3, d27);
	and (d27, d5, d22);
	or (d28, d29, d30);
	and (d29, d3, d21);
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, x1, d12);
	or (d33, d34, d35);
	and (d34, x0, d4);
	or (d35, d36, d37);
	and (d36, x0, d27);
	or (d37, d14, d20);
	assign f2 = d38;
	or (d38, d39, d40);
	and (d39, d3, d15);
	or (d40, d10, d41);
	or (d41, d29, d42);
	or (d42, d43, d44);
	and (d43, d3, d24);
	or (d44, d14, d45);
	or (d45, d18, d46);
	or (d46, d20, d47);
	and (d47, x0, d32);
	assign f3 = d48;
	or (d48, d26, d49);
	or (d49, d39, d50);
	or (d50, d29, d51);
	or (d51, d19, d43);
	assign f4 = d52;
	or (d52, d2, d53);
	or (d53, d26, d54);
	or (d54, d10, d55);
	or (d55, d29, d56);
	or (d56, d36, d57);
	or (d57, d18, d58);
	or (d58, d59, d61);
	and (d59, x0, d60);
	and (d60, x1, d6);
	or (d61, d20, d62);
	or (d62, d23, d47);
	assign f5 = d63;
	or (d63, d39, d64);
	or (d64, d10, d65);
	or (d65, d43, d66);
	or (d66, d14, d36);
endmodule
