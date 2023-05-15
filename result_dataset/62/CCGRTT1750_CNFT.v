//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1750_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

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
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, x2, d8);
	or (d24, d25, d26);
	and (d25, x0, d15);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d23);
	and (d29, x0, d18);
	assign f1 = d30;
	or (d30, d14, d31);
	or (d31, d32, d33);
	and (d32, d3, d28);
	or (d33, d34, d35);
	and (d34, x0, d4);
	or (d35, d24, d36);
	and (d36, x0, d37);
	and (d37, d5, d19);
	assign f2 = d38;
	or (d38, d10, d39);
	or (d39, d40, d41);
	and (d40, d3, d37);
	or (d41, d42, d44);
	and (d42, d3, d43);
	and (d43, x1, d6);
	or (d44, d14, d45);
	or (d45, d32, d46);
	or (d46, d17, d47);
	or (d47, d34, d48);
	or (d48, d49, d50);
	and (d49, x0, d11);
	or (d50, d36, d51);
	or (d51, d25, d27);
	assign f3 = d52;
	or (d52, d2, d53);
	or (d53, d54, d55);
	and (d54, d3, d22);
	or (d55, d40, d56);
	or (d56, d42, d57);
	or (d57, d14, d58);
	or (d58, d32, d59);
	or (d59, d34, d60);
	or (d60, d24, d49);
	assign f4 = d61;
	or (d61, d10, d62);
	or (d62, d54, d63);
	or (d63, d42, d64);
	or (d64, d14, d65);
	or (d65, d17, d66);
	or (d66, d34, d67);
	or (d67, d49, d68);
	or (d68, d21, d69);
	or (d69, d27, d36);
endmodule
