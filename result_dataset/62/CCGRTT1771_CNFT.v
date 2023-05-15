//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1771_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d13);
	and (d10, d3, d11);
	and (d11, d5, d12);
	and (d12, x2, x3);
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d6);
	or (d16, d17, d19);
	and (d17, d3, d18);
	and (d18, x1, d12);
	or (d19, d20, d21);
	and (d20, x0, d4);
	or (d21, d22, d23);
	and (d22, x0, d11);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, x1, d26);
	and (d26, d7, x3);
	or (d27, d28, d31);
	and (d28, x0, d29);
	and (d29, x1, d30);
	and (d30, x2, d8);
	and (d31, x0, d18);
	assign f1 = d32;
	or (d32, d2, d33);
	or (d33, d34, d36);
	and (d34, d3, d35);
	and (d35, d5, d26);
	or (d36, d10, d37);
	or (d37, d14, d38);
	or (d38, d39, d40);
	and (d39, d3, d25);
	or (d40, d20, d41);
	or (d41, d42, d43);
	and (d42, x0, d35);
	or (d43, d22, d27);
	assign f2 = d44;
	or (d44, d2, d45);
	or (d45, d46, d48);
	and (d46, d3, d47);
	and (d47, d5, d30);
	or (d48, d10, d49);
	or (d49, d14, d50);
	or (d50, d39, d51);
	or (d51, d42, d52);
	or (d52, d53, d54);
	and (d53, x0, d47);
	or (d54, d22, d55);
	or (d55, d24, d56);
	and (d56, x0, d15);
	assign f3 = d57;
	or (d57, d2, d58);
	or (d58, d34, d59);
	or (d59, d46, d60);
	or (d60, d14, d61);
	or (d61, d39, d62);
	or (d62, d53, d63);
	or (d63, d56, d64);
	or (d64, d24, d28);
	assign f4 = d65;
	or (d65, d2, d66);
	or (d66, d34, d67);
	or (d67, d46, d68);
	or (d68, d69, d70);
	and (d69, d3, d29);
	or (d70, d22, d28);
endmodule
