//f0 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1840_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	or (d13, d14, d15);
	and (d14, x0, d9);
	or (d15, d16, d19);
	and (d16, x0, d17);
	and (d17, x1, d18);
	and (d18, x3, d11);
	and (d19, x0, d20);
	and (d20, x1, d21);
	and (d21, x2, d12);
	assign f1 = d22;
	or (d22, d23, d25);
	and (d23, d3, d24);
	and (d24, d5, d10);
	or (d25, d8, d26);
	or (d26, d27, d28);
	and (d27, d3, d17);
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, x1, d6);
	or (d31, d32, d33);
	and (d32, x0, d24);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, d5, d18);
	or (d36, d16, d37);
	or (d37, d19, d38);
	and (d38, x0, d30);
	assign f2 = d39;
	or (d39, d40, d41);
	and (d40, d3, d35);
	or (d41, d27, d42);
	or (d42, d43, d44);
	and (d43, d3, d20);
	or (d44, d29, d45);
	or (d45, d46, d48);
	and (d46, x0, d47);
	and (d47, d5, d21);
	or (d48, d16, d38);
	assign f3 = d49;
	or (d49, d23, d50);
	or (d50, d40, d51);
	or (d51, d2, d52);
	or (d52, d8, d53);
	or (d53, d43, d54);
	or (d54, d29, d55);
	or (d55, d34, d56);
	or (d56, d15, d57);
	and (d57, x0, d4);
	assign f4 = d58;
	or (d58, d23, d59);
	or (d59, d27, d60);
	or (d60, d43, d61);
	or (d61, d32, d62);
	or (d62, d14, d37);
	assign f5 = d63;
	or (d63, d40, d64);
	or (d64, d2, d65);
	or (d65, d27, d36);
endmodule
