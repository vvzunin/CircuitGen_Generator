//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f6 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1940_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

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
	and (d18, x0, d19);
	and (d19, d5, d15);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, x1, d23);
	and (d23, d7, d16);
	or (d24, d25, d26);
	and (d25, x0, d14);
	and (d26, x0, d27);
	and (d27, x1, d11);
	assign f1 = d28;
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, d5, d23);
	or (d31, d32, d33);
	and (d32, d3, d19);
	or (d33, d13, d34);
	or (d34, d35, d36);
	and (d35, x0, d30);
	or (d36, d25, d37);
	and (d37, x0, d10);
	assign f2 = d38;
	or (d38, d29, d39);
	or (d39, d2, d40);
	or (d40, d32, d41);
	or (d41, d9, d42);
	or (d42, d43, d44);
	and (d43, d3, d22);
	or (d44, d45, d47);
	and (d45, d3, d46);
	and (d46, x1, d6);
	or (d47, d13, d48);
	or (d48, d49, d50);
	and (d49, x0, d4);
	or (d50, d21, d51);
	and (d51, x0, d46);
	assign f3 = d52;
	or (d52, d32, d53);
	or (d53, d9, d34);
	assign f4 = d54;
	or (d54, d29, d55);
	or (d55, d2, d56);
	or (d56, d32, d57);
	or (d57, d43, d58);
	or (d58, d45, d59);
	or (d59, d60, d61);
	and (d60, d3, d27);
	or (d61, d35, d62);
	or (d62, d49, d63);
	or (d63, d21, d64);
	or (d64, d26, d51);
	assign f5 = d65;
	or (d65, d2, d66);
	or (d66, d60, d67);
	or (d67, d21, d35);
	assign f6 = d68;
	or (d68, d9, d69);
	or (d69, d43, d70);
	or (d70, d13, d71);
	or (d71, d34, d60);
endmodule
