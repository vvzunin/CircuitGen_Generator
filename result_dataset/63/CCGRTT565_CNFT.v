//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT565_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

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
	and (d15, x3, d16);
	not (d16, x2);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d11);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, d5, d26);
	and (d26, d7, d16);
	or (d27, d28, d30);
	and (d28, x0, d29);
	and (d29, d5, d15);
	or (d30, d31, d32);
	and (d31, x0, d10);
	or (d32, d33, d34);
	and (d33, x0, d19);
	and (d34, x0, d22);
	assign f1 = d35;
	or (d35, d36, d37);
	and (d36, d3, d29);
	or (d37, d9, d38);
	or (d38, d13, d39);
	or (d39, d21, d40);
	or (d40, d28, d33);
	assign f2 = d41;
	or (d41, d36, d42);
	or (d42, d43, d45);
	and (d43, d3, d44);
	and (d44, x1, d26);
	or (d45, d18, d46);
	or (d46, d24, d47);
	or (d47, d28, d48);
	and (d48, x0, d14);
	assign f3 = d49;
	or (d49, d50, d51);
	and (d50, d3, d25);
	or (d51, d2, d52);
	or (d52, d9, d53);
	or (d53, d18, d54);
	or (d54, d21, d55);
	or (d55, d24, d56);
	or (d56, d57, d58);
	and (d57, x0, d4);
	or (d58, d31, d48);
	assign f4 = d59;
	or (d59, d50, d60);
	or (d60, d36, d61);
	or (d61, d18, d62);
	or (d62, d24, d63);
	or (d63, d57, d64);
	or (d64, d31, d65);
	or (d65, d32, d48);
	assign f5 = d66;
	or (d66, d18, d67);
	or (d67, d24, d68);
	or (d68, d28, d69);
	or (d69, d57, d70);
	or (d70, d31, d33);
endmodule
