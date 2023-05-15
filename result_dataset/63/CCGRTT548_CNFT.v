//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT548_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, x3);
	or (d12, d13, d17);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, d7, d16);
	not (d16, x2);
	or (d17, d18, d19);
	and (d18, x0, d4);
	or (d19, d20, d21);
	and (d20, x0, d14);
	and (d21, x0, d22);
	and (d22, x1, d11);
	assign f1 = d23;
	or (d23, d2, d24);
	or (d24, d13, d25);
	or (d25, d26, d28);
	and (d26, d3, d27);
	and (d27, x1, d6);
	or (d28, d29, d30);
	and (d29, d3, d22);
	or (d30, d18, d31);
	or (d31, d32, d33);
	and (d32, x0, d10);
	or (d33, d20, d34);
	or (d34, d35, d38);
	and (d35, x0, d36);
	and (d36, x1, d37);
	and (d37, x3, d16);
	or (d38, d21, d39);
	and (d39, x0, d27);
	assign f2 = d40;
	or (d40, d41, d43);
	and (d41, d3, d42);
	and (d42, d5, d15);
	or (d43, d9, d44);
	or (d44, d45, d46);
	and (d45, d3, d36);
	or (d46, d26, d47);
	or (d47, d29, d48);
	or (d48, d49, d50);
	and (d49, x0, d42);
	or (d50, d18, d51);
	or (d51, d21, d35);
	assign f3 = d52;
	or (d52, d41, d53);
	or (d53, d9, d54);
	or (d54, d26, d55);
	or (d55, d21, d56);
	and (d56, x0, d57);
	and (d57, d5, d37);
	assign f4 = d58;
	or (d58, d41, d59);
	or (d59, d60, d61);
	and (d60, d3, d57);
	or (d61, d45, d62);
	or (d62, d31, d56);
	assign f5 = d63;
	or (d63, d13, d64);
	or (d64, d45, d65);
	or (d65, d26, d66);
	or (d66, d29, d67);
	or (d67, d31, d49);
endmodule
