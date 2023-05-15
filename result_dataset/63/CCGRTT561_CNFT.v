//f0 = (not x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3)
module CCGRTT561_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	and (d5, x2, d6);
	not (d6, x3);
	or (d7, d8, d9);
	and (d8, x0, d4);
	and (d9, x0, d10);
	and (d10, x1, d11);
	and (d11, x2, x3);
	assign f1 = d12;
	or (d12, d13, d18);
	and (d13, d3, d14);
	and (d14, d15, d16);
	not (d15, x1);
	and (d16, d6, d17);
	not (d17, x2);
	or (d18, d19, d22);
	and (d19, d3, d20);
	and (d20, d15, d21);
	and (d21, x3, d17);
	or (d22, d23, d25);
	and (d23, d3, d24);
	and (d24, d11, d15);
	or (d25, d26, d28);
	and (d26, d3, d27);
	and (d27, x1, d16);
	or (d28, d2, d29);
	or (d29, d30, d31);
	and (d30, d3, d10);
	or (d31, d32, d33);
	and (d32, x0, d14);
	or (d33, d34, d35);
	and (d34, x0, d20);
	or (d35, d36, d38);
	and (d36, x0, d37);
	and (d37, d5, d15);
	or (d38, d9, d39);
	and (d39, x0, d40);
	and (d40, x1, d21);
	assign f2 = d41;
	or (d41, d13, d42);
	or (d42, d23, d43);
	or (d43, d26, d44);
	or (d44, d45, d46);
	and (d45, d3, d40);
	or (d46, d2, d47);
	or (d47, d30, d48);
	or (d48, d32, d49);
	or (d49, d36, d50);
	or (d50, d39, d51);
	and (d51, x0, d27);
	assign f3 = d52;
	or (d52, d26, d53);
	or (d53, d36, d54);
	or (d54, d55, d56);
	and (d55, x0, d24);
	or (d56, d38, d51);
	assign f4 = d57;
	or (d57, d13, d58);
	or (d58, d59, d60);
	and (d59, d3, d37);
	or (d60, d23, d61);
	or (d61, d26, d62);
	or (d62, d30, d63);
	or (d63, d36, d64);
	or (d64, d8, d39);
	assign f5 = d65;
	or (d65, d19, d66);
	or (d66, d2, d67);
	or (d67, d32, d34);
endmodule
