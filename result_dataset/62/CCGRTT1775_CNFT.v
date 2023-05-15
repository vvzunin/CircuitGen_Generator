//f0 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1775_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	and (d5, d6, d7);
	not (d6, x2);
	not (d7, x3);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, x1, d11);
	and (d11, d6, x3);
	or (d12, d13, d16);
	and (d13, x0, d14);
	and (d14, d11, d15);
	not (d15, x1);
	or (d16, d17, d20);
	and (d17, x0, d18);
	and (d18, d15, d19);
	and (d19, x2, x3);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d23, d24);
	and (d23, x0, d10);
	and (d24, x0, d25);
	and (d25, x1, d26);
	and (d26, x2, d7);
	assign f1 = d27;
	or (d27, d28, d29);
	and (d28, d3, d14);
	or (d29, d30, d32);
	and (d30, d3, d31);
	and (d31, d15, d26);
	or (d32, d33, d34);
	and (d33, d3, d18);
	or (d34, d2, d35);
	or (d35, d36, d37);
	and (d36, d3, d25);
	or (d37, d13, d38);
	or (d38, d17, d39);
	or (d39, d21, d23);
	assign f2 = d40;
	or (d40, d41, d43);
	and (d41, d3, d42);
	and (d42, d5, d15);
	or (d43, d13, d44);
	and (d44, x0, d31);
	assign f3 = d45;
	or (d45, d41, d46);
	or (d46, d28, d47);
	or (d47, d30, d48);
	or (d48, d33, d49);
	or (d49, d2, d50);
	or (d50, d9, d51);
	or (d51, d36, d52);
	or (d52, d53, d54);
	and (d53, x0, d42);
	or (d54, d13, d55);
	or (d55, d44, d56);
	or (d56, d17, d24);
	assign f4 = d57;
	or (d57, d41, d58);
	or (d58, d28, d59);
	or (d59, d2, d60);
	or (d60, d36, d61);
	or (d61, d44, d62);
	or (d62, d23, d63);
	and (d63, x0, d64);
	and (d64, x1, d19);
endmodule
