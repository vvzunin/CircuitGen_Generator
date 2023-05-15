//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT547_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	or (d11, d12, d16);
	and (d12, x0, d13);
	and (d13, d5, d14);
	and (d14, x3, d15);
	not (d15, x2);
	or (d16, d17, d18);
	and (d17, x0, d4);
	or (d18, d19, d22);
	and (d19, x0, d20);
	and (d20, d5, d21);
	and (d21, x2, x3);
	or (d22, d23, d26);
	and (d23, x0, d24);
	and (d24, x1, d25);
	and (d25, d7, d15);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d14);
	and (d29, x0, d30);
	and (d30, x1, d21);
	assign f1 = d31;
	or (d31, d2, d32);
	or (d32, d9, d33);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, d5, d25);
	or (d36, d12, d37);
	or (d37, d19, d38);
	or (d38, d23, d39);
	or (d39, d27, d40);
	and (d40, x0, d10);
	assign f2 = d41;
	or (d41, d42, d43);
	and (d42, d3, d35);
	or (d43, d44, d45);
	and (d44, d3, d13);
	or (d45, d46, d47);
	and (d46, d3, d20);
	or (d47, d48, d49);
	and (d48, d3, d28);
	or (d49, d9, d50);
	or (d50, d34, d51);
	or (d51, d12, d38);
	assign f3 = d52;
	or (d52, d2, d53);
	or (d53, d46, d54);
	or (d54, d34, d55);
	or (d55, d12, d56);
	or (d56, d17, d38);
	assign f4 = d57;
	or (d57, d46, d58);
	or (d58, d59, d60);
	and (d59, d3, d24);
	or (d60, d48, d51);
	assign f5 = d61;
	or (d61, d44, d62);
	or (d62, d46, d63);
	or (d63, d59, d64);
	or (d64, d9, d65);
	or (d65, d17, d66);
	or (d66, d23, d40);
endmodule
