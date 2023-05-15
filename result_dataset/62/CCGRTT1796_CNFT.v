//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f4 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3)
module CCGRTT1796_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63;

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
	and (d12, d7, x3);
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d12);
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, x2, x3);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d23, d24);
	and (d23, x0, d11);
	or (d24, d25, d28);
	and (d25, x0, d26);
	and (d26, d5, d27);
	and (d27, x2, d8);
	and (d28, x0, d29);
	and (d29, x1, d6);
	assign f1 = d30;
	or (d30, d2, d31);
	or (d31, d10, d32);
	or (d32, d33, d34);
	and (d33, d3, d26);
	or (d34, d35, d37);
	and (d35, d3, d36);
	and (d36, d5, d19);
	or (d37, d38, d39);
	and (d38, d3, d29);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, x1, d27);
	or (d42, d21, d43);
	or (d43, d25, d44);
	or (d44, d28, d45);
	or (d45, d46, d47);
	and (d46, x0, d15);
	and (d47, x0, d41);
	assign f2 = d48;
	or (d48, d2, d49);
	or (d49, d35, d50);
	or (d50, d14, d51);
	or (d51, d17, d52);
	and (d52, x0, d18);
	assign f3 = d53;
	or (d53, d10, d54);
	or (d54, d33, d55);
	or (d55, d35, d56);
	or (d56, d38, d57);
	or (d57, d14, d58);
	or (d58, d21, d59);
	or (d59, d28, d60);
	and (d60, x0, d36);
	assign f4 = d61;
	or (d61, d38, d62);
	or (d62, d40, d63);
	or (d63, d23, d46);
endmodule
