//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1821_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d13);
	and (d9, d3, d10);
	and (d10, x1, d11);
	and (d11, d7, d12);
	not (d12, x3);
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d6);
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, x2, d12);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d5, d11);
	or (d23, d24, d26);
	and (d24, x0, d25);
	and (d25, d5, d19);
	or (d26, d27, d30);
	and (d27, x0, d28);
	and (d28, d5, d29);
	and (d29, x2, x3);
	and (d30, x0, d31);
	and (d31, x1, d29);
	assign f1 = d32;
	or (d32, d33, d34);
	and (d33, d3, d28);
	or (d34, d14, d35);
	or (d35, d17, d36);
	or (d36, d37, d38);
	and (d37, x0, d4);
	or (d38, d27, d39);
	or (d39, d40, d41);
	and (d40, x0, d10);
	or (d41, d30, d42);
	and (d42, x0, d18);
	assign f2 = d43;
	or (d43, d44, d45);
	and (d44, d3, d22);
	or (d45, d46, d47);
	and (d46, d3, d25);
	or (d47, d33, d48);
	or (d48, d9, d49);
	or (d49, d50, d51);
	and (d50, d3, d31);
	or (d51, d21, d52);
	or (d52, d24, d53);
	or (d53, d27, d54);
	or (d54, d41, d55);
	and (d55, x0, d15);
	assign f3 = d56;
	or (d56, d46, d57);
	or (d57, d9, d58);
	or (d58, d14, d59);
	or (d59, d17, d60);
	or (d60, d21, d61);
	or (d61, d30, d55);
	assign f4 = d62;
	or (d62, d44, d63);
	or (d63, d33, d64);
	or (d64, d9, d65);
	or (d65, d21, d41);
	assign f5 = d66;
	or (d66, d44, d67);
	or (d67, d14, d68);
	or (d68, d50, d69);
	or (d69, d21, d70);
	or (d70, d37, d71);
	or (d71, d40, d61);
endmodule
