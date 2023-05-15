//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT550_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d13);
	and (d9, d3, d10);
	and (d10, x1, d11);
	and (d11, d7, d12);
	not (d12, x2);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, x0, d19);
	and (d19, d5, d11);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d5, d16);
	and (d23, x0, d15);
	assign f1 = d24;
	or (d24, d25, d28);
	and (d25, d3, d26);
	and (d26, d5, d27);
	and (d27, x3, d12);
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, x1, d27);
	or (d31, d14, d32);
	or (d32, d18, d33);
	or (d33, d21, d34);
	or (d34, d23, d35);
	and (d35, x0, d10);
	assign f2 = d36;
	or (d36, d37, d39);
	and (d37, d3, d38);
	and (d38, x1, d6);
	or (d39, d14, d40);
	or (d40, d34, d41);
	and (d41, x0, d26);
	assign f3 = d42;
	or (d42, d2, d43);
	or (d43, d9, d44);
	or (d44, d18, d45);
	or (d45, d41, d46);
	and (d46, x0, d4);
	assign f4 = d47;
	or (d47, d25, d48);
	or (d48, d2, d49);
	or (d49, d50, d51);
	and (d50, d3, d22);
	or (d51, d9, d52);
	or (d52, d37, d53);
	or (d53, d14, d54);
	or (d54, d18, d55);
	or (d55, d41, d56);
	or (d56, d35, d57);
	or (d57, d58, d59);
	and (d58, x0, d30);
	and (d59, x0, d38);
	assign f5 = d60;
	or (d60, d61, d62);
	and (d61, d3, d19);
	or (d62, d25, d63);
	or (d63, d37, d64);
	or (d64, d14, d65);
	or (d65, d18, d66);
	or (d66, d23, d46);
endmodule
