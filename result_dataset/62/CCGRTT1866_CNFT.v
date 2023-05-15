//f0 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3)
module CCGRTT1866_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	or (d12, d13, d17);
	and (d13, x0, d14);
	and (d14, d15, d16);
	not (d15, x1);
	and (d16, d6, d11);
	or (d17, d18, d20);
	and (d18, x0, d19);
	and (d19, d10, d15);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d15, d23);
	and (d23, x2, x3);
	and (d24, x0, d4);
	assign f1 = d25;
	or (d25, d26, d27);
	and (d26, d3, d14);
	or (d27, d28, d30);
	and (d28, d3, d29);
	and (d29, d5, d15);
	or (d30, d31, d32);
	and (d31, d3, d19);
	or (d32, d8, d33);
	or (d33, d34, d35);
	and (d34, x0, d29);
	or (d35, d18, d36);
	or (d36, d21, d37);
	or (d37, d38, d40);
	and (d38, x0, d39);
	and (d39, x1, d16);
	or (d40, d24, d41);
	and (d41, x0, d9);
	assign f2 = d42;
	or (d42, d28, d43);
	or (d43, d44, d45);
	and (d44, d3, d39);
	or (d45, d8, d46);
	or (d46, d47, d49);
	and (d47, d3, d48);
	and (d48, x1, d23);
	or (d49, d34, d50);
	or (d50, d18, d51);
	and (d51, x0, d48);
	assign f3 = d52;
	or (d52, d31, d53);
	or (d53, d54, d55);
	and (d54, d3, d22);
	or (d55, d44, d56);
	or (d56, d8, d57);
	or (d57, d13, d58);
	or (d58, d18, d59);
	or (d59, d38, d51);
	assign f4 = d60;
	or (d60, d31, d61);
	or (d61, d8, d62);
	or (d62, d21, d40);
	assign f5 = d63;
	or (d63, d44, d64);
	or (d64, d47, d65);
	or (d65, d13, d66);
	or (d66, d18, d34);
endmodule
