//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1896_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

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
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d12);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d16);
	or (d23, d24, d25);
	and (d24, x0, d4);
	or (d25, d26, d29);
	and (d26, x0, d27);
	and (d27, d5, d28);
	and (d28, x2, d8);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, x1, d6);
	or (d32, d33, d34);
	and (d33, x0, d19);
	and (d34, x0, d35);
	and (d35, x1, d28);
	assign f1 = d36;
	or (d36, d37, d38);
	and (d37, d3, d27);
	or (d38, d14, d39);
	or (d39, d18, d40);
	or (d40, d41, d42);
	and (d41, d3, d35);
	or (d42, d21, d32);
	assign f2 = d43;
	or (d43, d41, d44);
	or (d44, d21, d45);
	or (d45, d32, d46);
	and (d46, x0, d11);
	assign f3 = d47;
	or (d47, d10, d48);
	or (d48, d37, d49);
	or (d49, d50, d51);
	and (d50, d3, d31);
	or (d51, d46, d52);
	or (d52, d26, d53);
	and (d53, x0, d22);
	assign f4 = d54;
	or (d54, d2, d55);
	or (d55, d37, d56);
	or (d56, d14, d57);
	or (d57, d50, d58);
	or (d58, d21, d59);
	or (d59, d46, d60);
	or (d60, d30, d61);
	or (d61, d34, d53);
	assign f5 = d62;
	or (d62, d37, d63);
	or (d63, d14, d64);
	or (d64, d18, d65);
	or (d65, d21, d66);
	or (d66, d46, d67);
	or (d67, d30, d34);
endmodule
