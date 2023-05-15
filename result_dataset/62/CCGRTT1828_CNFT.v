//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
module CCGRTT1828_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d11);
	and (d9, d3, d10);
	and (d10, x1, d6);
	or (d11, d12, d15);
	and (d12, d3, d13);
	and (d13, x1, d14);
	and (d14, x2, x3);
	or (d15, d16, d20);
	and (d16, x0, d17);
	and (d17, d5, d18);
	and (d18, x3, d19);
	not (d19, x2);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d23, d26);
	and (d23, x0, d24);
	and (d24, x1, d25);
	and (d25, d7, d19);
	and (d26, x0, d27);
	and (d27, x1, d18);
	assign f1 = d28;
	or (d28, d29, d30);
	and (d29, d3, d17);
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d14);
	or (d33, d34, d35);
	and (d34, d3, d24);
	or (d35, d12, d36);
	or (d36, d22, d37);
	and (d37, x0, d32);
	assign f2 = d38;
	or (d38, d29, d39);
	or (d39, d2, d40);
	or (d40, d41, d42);
	and (d41, d3, d27);
	or (d42, d12, d43);
	or (d43, d21, d44);
	or (d44, d37, d45);
	or (d45, d26, d46);
	and (d46, x0, d13);
	assign f3 = d47;
	or (d47, d29, d48);
	or (d48, d31, d49);
	or (d49, d41, d50);
	or (d50, d12, d51);
	or (d51, d21, d52);
	or (d52, d37, d53);
	or (d53, d46, d54);
	and (d54, x0, d10);
	assign f4 = d55;
	or (d55, d56, d58);
	and (d56, d3, d57);
	and (d57, d5, d25);
	or (d58, d29, d59);
	or (d59, d2, d60);
	or (d60, d31, d61);
	or (d61, d34, d62);
	or (d62, d41, d63);
	or (d63, d9, d64);
	or (d64, d12, d65);
	or (d65, d16, d66);
	or (d66, d23, d54);
	assign f5 = d67;
	or (d67, d29, d68);
	or (d68, d12, d69);
	or (d69, d16, d36);
endmodule
