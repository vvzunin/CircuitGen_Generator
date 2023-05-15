//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1832_CNFT(
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
	or (d8, d9, d11);
	and (d9, d3, d10);
	and (d10, x1, d6);
	or (d11, d12, d13);
	and (d12, x0, d4);
	or (d13, d14, d18);
	and (d14, x0, d15);
	and (d15, x1, d16);
	and (d16, d7, d17);
	not (d17, x2);
	or (d18, d19, d22);
	and (d19, x0, d20);
	and (d20, x1, d21);
	and (d21, x3, d17);
	and (d22, x0, d23);
	and (d23, x1, d24);
	and (d24, x2, x3);
	assign f1 = d25;
	or (d25, d26, d28);
	and (d26, d3, d27);
	and (d27, d5, d24);
	or (d28, d9, d29);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, d5, d16);
	or (d32, d12, d33);
	or (d33, d34, d35);
	and (d34, x0, d27);
	or (d35, d14, d36);
	or (d36, d19, d37);
	or (d37, d22, d38);
	and (d38, x0, d10);
	assign f2 = d39;
	or (d39, d2, d40);
	or (d40, d26, d41);
	or (d41, d42, d43);
	and (d42, d3, d23);
	or (d43, d30, d44);
	or (d44, d45, d47);
	and (d45, x0, d46);
	and (d46, d5, d21);
	or (d47, d34, d48);
	or (d48, d14, d22);
	assign f3 = d49;
	or (d49, d50, d51);
	and (d50, d3, d31);
	or (d51, d52, d53);
	and (d52, d3, d46);
	or (d53, d2, d54);
	or (d54, d55, d56);
	and (d55, d3, d15);
	or (d56, d9, d57);
	or (d57, d42, d58);
	or (d58, d30, d47);
	assign f4 = d59;
	or (d59, d9, d60);
	or (d60, d45, d61);
	or (d61, d34, d62);
	or (d62, d14, d37);
	assign f5 = d63;
	or (d63, d50, d64);
	or (d64, d26, d65);
	or (d65, d66, d67);
	and (d66, d3, d20);
	or (d67, d30, d68);
	or (d68, d12, d69);
	or (d69, d14, d70);
	or (d70, d19, d38);
endmodule
