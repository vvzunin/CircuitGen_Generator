//f0 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3)
module CCGRTT526_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	and (d5, d6, x3);
	not (d6, x2);
	or (d7, d8, d12);
	and (d8, d3, d9);
	and (d9, x1, d10);
	and (d10, x2, d11);
	not (d11, x3);
	or (d12, d13, d16);
	and (d13, x0, d14);
	and (d14, d5, d15);
	not (d15, x1);
	or (d16, d17, d19);
	and (d17, x0, d18);
	and (d18, d10, d15);
	or (d19, d20, d23);
	and (d20, x0, d21);
	and (d21, x1, d22);
	and (d22, d6, d11);
	and (d23, x0, d9);
	assign f1 = d24;
	or (d24, d25, d27);
	and (d25, d3, d26);
	and (d26, d15, d22);
	or (d27, d28, d29);
	and (d28, d3, d14);
	or (d29, d30, d31);
	and (d30, d3, d21);
	or (d31, d2, d32);
	or (d32, d8, d33);
	or (d33, d34, d37);
	and (d34, d3, d35);
	and (d35, x1, d36);
	and (d36, x2, x3);
	or (d37, d38, d39);
	and (d38, x0, d26);
	or (d39, d13, d40);
	or (d40, d17, d41);
	or (d41, d20, d42);
	and (d42, x0, d35);
	assign f2 = d43;
	or (d43, d25, d44);
	or (d44, d30, d45);
	or (d45, d8, d46);
	or (d46, d34, d47);
	or (d47, d17, d48);
	or (d48, d20, d49);
	or (d49, d50, d51);
	and (d50, x0, d4);
	or (d51, d23, d42);
	assign f3 = d52;
	or (d52, d25, d53);
	or (d53, d28, d54);
	or (d54, d55, d56);
	and (d55, d3, d18);
	or (d56, d30, d57);
	or (d57, d2, d58);
	or (d58, d8, d59);
	or (d59, d34, d60);
	or (d60, d38, d50);
	assign f4 = d61;
	or (d61, d25, d62);
	or (d62, d28, d63);
	or (d63, d55, d64);
	or (d64, d2, d65);
	or (d65, d8, d17);
endmodule
