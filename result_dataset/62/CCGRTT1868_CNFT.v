//f0 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1868_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, x3);
	or (d7, d8, d13);
	and (d8, d3, d9);
	and (d9, x1, d10);
	and (d10, d11, d12);
	not (d11, x2);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x3, d11);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d5, d10);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, d5, d26);
	and (d26, x2, d12);
	or (d27, d28, d29);
	and (d28, x0, d4);
	or (d29, d30, d31);
	and (d30, x0, d15);
	or (d31, d32, d34);
	and (d32, x0, d33);
	and (d33, x1, d26);
	and (d34, x0, d19);
	assign f1 = d35;
	or (d35, d36, d37);
	and (d36, d3, d22);
	or (d37, d38, d39);
	and (d38, d3, d25);
	or (d39, d8, d40);
	or (d40, d41, d42);
	and (d41, d3, d33);
	or (d42, d43, d45);
	and (d43, x0, d44);
	and (d44, d5, d16);
	or (d45, d28, d46);
	or (d46, d47, d48);
	and (d47, x0, d9);
	or (d48, d30, d34);
	assign f2 = d49;
	or (d49, d36, d50);
	or (d50, d51, d52);
	and (d51, d3, d44);
	or (d52, d2, d53);
	or (d53, d41, d54);
	or (d54, d21, d55);
	or (d55, d47, d56);
	or (d56, d30, d32);
	assign f3 = d57;
	or (d57, d36, d58);
	or (d58, d2, d59);
	or (d59, d8, d60);
	or (d60, d32, d47);
	assign f4 = d61;
	or (d61, d36, d62);
	or (d62, d51, d63);
	or (d63, d2, d64);
	or (d64, d8, d65);
	or (d65, d14, d66);
	or (d66, d18, d67);
	or (d67, d43, d56);
	assign f5 = d68;
	or (d68, d51, d69);
	or (d69, d14, d70);
	or (d70, d21, d71);
	or (d71, d27, d43);
endmodule
