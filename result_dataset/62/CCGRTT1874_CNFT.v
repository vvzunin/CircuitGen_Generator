//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
module CCGRTT1874_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
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
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, d8);
	or (d17, d18, d19);
	and (d18, x0, d11);
	or (d19, d20, d23);
	and (d20, x0, d21);
	and (d21, d5, d22);
	and (d22, x2, x3);
	and (d23, x0, d15);
	assign f1 = d24;
	or (d24, d25, d27);
	and (d25, d3, d26);
	and (d26, d5, d16);
	or (d27, d28, d29);
	and (d28, d3, d21);
	or (d29, d30, d31);
	and (d30, x0, d4);
	or (d31, d20, d32);
	or (d32, d23, d33);
	and (d33, x0, d34);
	and (d34, x1, d6);
	assign f2 = d35;
	or (d35, d25, d36);
	or (d36, d28, d37);
	or (d37, d38, d39);
	and (d38, d3, d34);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, x1, d12);
	or (d42, d14, d43);
	or (d43, d44, d46);
	and (d44, d3, d45);
	and (d45, x1, d22);
	or (d46, d18, d47);
	or (d47, d20, d48);
	or (d48, d33, d49);
	and (d49, x0, d41);
	assign f3 = d50;
	or (d50, d25, d51);
	or (d51, d38, d52);
	or (d52, d44, d53);
	or (d53, d54, d55);
	and (d54, x0, d26);
	or (d55, d20, d56);
	or (d56, d33, d57);
	or (d57, d49, d58);
	and (d58, x0, d45);
	assign f4 = d59;
	or (d59, d2, d60);
	or (d60, d25, d61);
	or (d61, d14, d62);
	or (d62, d44, d63);
	or (d63, d30, d64);
	or (d64, d23, d58);
	assign f5 = d65;
	or (d65, d2, d66);
	or (d66, d25, d67);
	or (d67, d38, d68);
	or (d68, d40, d69);
	or (d69, d14, d20);
endmodule
