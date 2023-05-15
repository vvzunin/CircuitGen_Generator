//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1834_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d12, x2, d8);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, x1, d23);
	and (d23, d7, x3);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, x1, d12);
	and (d27, x0, d28);
	and (d28, x1, d16);
	assign f1 = d29;
	or (d29, d30, d32);
	and (d30, d3, d31);
	and (d31, d5, d23);
	or (d32, d14, d33);
	or (d33, d18, d34);
	or (d34, d35, d36);
	and (d35, d3, d22);
	or (d36, d37, d38);
	and (d37, d3, d26);
	or (d38, d39, d40);
	and (d39, d3, d28);
	or (d40, d41, d42);
	and (d41, x0, d15);
	and (d42, x0, d19);
	assign f2 = d43;
	or (d43, d2, d44);
	or (d44, d18, d45);
	or (d45, d46, d47);
	and (d46, x0, d4);
	or (d47, d48, d49);
	and (d48, x0, d31);
	or (d49, d27, d42);
	assign f3 = d50;
	or (d50, d2, d51);
	or (d51, d30, d52);
	or (d52, d35, d53);
	or (d53, d24, d46);
	assign f4 = d54;
	or (d54, d35, d55);
	or (d55, d39, d56);
	or (d56, d42, d57);
	or (d57, d21, d25);
	assign f5 = d58;
	or (d58, d2, d59);
	or (d59, d30, d60);
	or (d60, d10, d61);
	or (d61, d14, d62);
	or (d62, d18, d63);
	or (d63, d37, d64);
	or (d64, d46, d65);
	or (d65, d48, d66);
	or (d66, d41, d49);
endmodule
