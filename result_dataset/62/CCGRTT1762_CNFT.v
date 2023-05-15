//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1762_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	or (d12, d13, d15);
	and (d13, d3, d14);
	and (d14, x1, d11);
	or (d15, d16, d20);
	and (d16, x0, d17);
	and (d17, d5, d18);
	and (d18, x3, d19);
	not (d19, x2);
	or (d20, d21, d22);
	and (d21, x0, d10);
	or (d22, d23, d26);
	and (d23, x0, d24);
	and (d24, x1, d25);
	and (d25, d7, d19);
	and (d26, x0, d14);
	assign f1 = d27;
	or (d27, d28, d29);
	and (d28, d3, d17);
	or (d29, d9, d30);
	or (d30, d31, d32);
	and (d31, d3, d24);
	or (d32, d33, d35);
	and (d33, d3, d34);
	and (d34, x1, d6);
	or (d35, d13, d36);
	or (d36, d26, d37);
	and (d37, x0, d4);
	assign f2 = d38;
	or (d38, d39, d41);
	and (d39, d3, d40);
	and (d40, d5, d25);
	or (d41, d28, d42);
	or (d42, d31, d43);
	or (d43, d44, d46);
	and (d44, d3, d45);
	and (d45, x1, d18);
	or (d46, d13, d47);
	or (d47, d16, d48);
	or (d48, d37, d49);
	or (d49, d23, d50);
	or (d50, d51, d52);
	and (d51, x0, d45);
	and (d52, x0, d34);
	assign f3 = d53;
	or (d53, d39, d54);
	or (d54, d28, d55);
	or (d55, d2, d56);
	or (d56, d31, d57);
	or (d57, d33, d58);
	or (d58, d59, d60);
	and (d59, x0, d40);
	or (d60, d21, d61);
	or (d61, d23, d52);
	assign f4 = d62;
	or (d62, d28, d63);
	or (d63, d31, d64);
	or (d64, d13, d65);
	or (d65, d16, d50);
endmodule
