//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1707_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

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
	and (d10, d5, d11);
	and (d11, x2, d12);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, d7, d12);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d11);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, d5, d20);
	or (d27, d28, d29);
	and (d28, x0, d10);
	or (d29, d30, d31);
	and (d30, x0, d15);
	and (d31, x0, d32);
	and (d32, x1, d16);
	assign f1 = d33;
	or (d33, d14, d34);
	or (d34, d18, d35);
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, x1, d6);
	or (d38, d39, d40);
	and (d39, d3, d32);
	or (d40, d25, d41);
	or (d41, d28, d42);
	or (d42, d43, d44);
	and (d43, x0, d37);
	or (d44, d31, d45);
	and (d45, x0, d23);
	assign f2 = d46;
	or (d46, d2, d47);
	or (d47, d36, d48);
	or (d48, d22, d49);
	or (d49, d25, d50);
	or (d50, d30, d51);
	and (d51, x0, d19);
	assign f3 = d52;
	or (d52, d53, d54);
	and (d53, d3, d26);
	or (d54, d2, d55);
	or (d55, d9, d56);
	or (d56, d14, d57);
	or (d57, d36, d58);
	or (d58, d59, d60);
	and (d59, x0, d4);
	or (d60, d28, d61);
	or (d61, d31, d51);
	assign f4 = d62;
	or (d62, d2, d63);
	or (d63, d9, d64);
	or (d64, d14, d65);
	or (d65, d18, d66);
	or (d66, d22, d67);
	or (d67, d39, d68);
	or (d68, d25, d69);
	or (d69, d45, d51);
endmodule
