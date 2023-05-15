//f0 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1837_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, x3);
	or (d7, d8, d10);
	and (d8, d3, d9);
	and (d9, x1, d6);
	or (d10, d11, d16);
	and (d11, x0, d12);
	and (d12, d5, d13);
	and (d13, d14, d15);
	not (d14, x2);
	not (d15, x3);
	or (d16, d17, d20);
	and (d17, x0, d18);
	and (d18, d5, d19);
	and (d19, x3, d14);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, x2, d15);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d23);
	and (d29, x0, d9);
	assign f1 = d30;
	or (d30, d31, d32);
	and (d31, d3, d12);
	or (d32, d33, d34);
	and (d33, d3, d18);
	or (d34, d2, d35);
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, x1, d13);
	or (d38, d39, d40);
	and (d39, d3, d28);
	or (d40, d11, d41);
	or (d41, d17, d42);
	and (d42, x0, d37);
	assign f2 = d43;
	or (d43, d31, d44);
	or (d44, d45, d46);
	and (d45, d3, d22);
	or (d46, d11, d47);
	or (d47, d21, d48);
	or (d48, d25, d27);
	assign f3 = d49;
	or (d49, d33, d50);
	or (d50, d8, d51);
	or (d51, d17, d52);
	or (d52, d21, d25);
	assign f4 = d53;
	or (d53, d31, d54);
	or (d54, d33, d55);
	or (d55, d45, d56);
	or (d56, d2, d57);
	or (d57, d8, d58);
	or (d58, d17, d59);
	or (d59, d27, d42);
	assign f5 = d60;
	or (d60, d31, d61);
	or (d61, d33, d62);
	or (d62, d2, d63);
	or (d63, d36, d64);
	or (d64, d65, d67);
	and (d65, d3, d66);
	and (d66, x1, d19);
	or (d67, d11, d68);
	or (d68, d25, d59);
endmodule
