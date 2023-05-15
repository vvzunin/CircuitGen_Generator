//f0 = (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
module CCGRTT556_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, x0, d3);
	and (d3, x1, d4);
	and (d4, d5, d6);
	not (d5, x2);
	not (d6, x3);
	or (d7, d8, d11);
	and (d8, x0, d9);
	and (d9, x1, d10);
	and (d10, d5, x3);
	and (d11, x0, d12);
	and (d12, x1, d13);
	and (d13, x2, d6);
	assign f1 = d14;
	or (d14, d15, d19);
	and (d15, d16, d17);
	not (d16, x0);
	and (d17, d4, d18);
	not (d18, x1);
	or (d19, d20, d23);
	and (d20, d16, d21);
	and (d21, d18, d22);
	and (d22, x2, x3);
	or (d23, d24, d25);
	and (d24, d12, d16);
	or (d25, d26, d28);
	and (d26, x0, d27);
	and (d27, d10, d18);
	or (d28, d2, d8);
	assign f2 = d29;
	or (d29, d15, d30);
	or (d30, d31, d32);
	and (d31, d3, d16);
	or (d32, d33, d34);
	and (d33, d9, d16);
	or (d34, d24, d35);
	or (d35, d36, d38);
	and (d36, d16, d37);
	and (d37, x1, d22);
	or (d38, d26, d39);
	or (d39, d11, d40);
	and (d40, x0, d37);
	assign f3 = d41;
	or (d41, d42, d44);
	and (d42, d16, d43);
	and (d43, d13, d18);
	or (d44, d20, d45);
	or (d45, d24, d46);
	or (d46, d47, d48);
	and (d47, x0, d17);
	or (d48, d11, d49);
	and (d49, x0, d21);
	assign f4 = d50;
	or (d50, d51, d52);
	and (d51, d16, d27);
	or (d52, d33, d53);
	or (d53, d54, d55);
	and (d54, x0, d43);
	or (d55, d49, d56);
	or (d56, d8, d39);
	assign f5 = d57;
	or (d57, d15, d58);
	or (d58, d31, d59);
	or (d59, d33, d60);
	or (d60, d24, d61);
	or (d61, d36, d62);
	or (d62, d26, d63);
	or (d63, d54, d64);
	or (d64, d8, d49);
endmodule
