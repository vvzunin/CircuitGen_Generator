//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1730_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

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
	and (d16, x3, d12);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, x2, x3);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, d5, d16);
	or (d27, d28, d29);
	and (d28, x0, d10);
	or (d29, d30, d31);
	and (d30, x0, d15);
	and (d31, x0, d19);
	assign f1 = d32;
	or (d32, d33, d35);
	and (d33, d3, d34);
	and (d34, d5, d11);
	or (d35, d2, d36);
	or (d36, d37, d39);
	and (d37, d3, d38);
	and (d38, d5, d23);
	or (d39, d9, d40);
	or (d40, d14, d41);
	or (d41, d18, d42);
	or (d42, d21, d43);
	or (d43, d44, d45);
	and (d44, x0, d38);
	or (d45, d28, d46);
	or (d46, d30, d47);
	or (d47, d31, d48);
	and (d48, x0, d22);
	assign f2 = d49;
	or (d49, d50, d51);
	and (d50, d3, d26);
	or (d51, d2, d52);
	or (d52, d14, d53);
	or (d53, d29, d54);
	and (d54, x0, d4);
	assign f3 = d55;
	or (d55, d50, d56);
	or (d56, d2, d57);
	or (d57, d9, d58);
	or (d58, d59, d60);
	and (d59, x0, d34);
	or (d60, d25, d61);
	or (d61, d54, d62);
	or (d62, d28, d31);
	assign f4 = d63;
	or (d63, d33, d64);
	or (d64, d50, d65);
	or (d65, d37, d66);
	or (d66, d21, d67);
	or (d67, d28, d68);
	or (d68, d30, d48);
endmodule
