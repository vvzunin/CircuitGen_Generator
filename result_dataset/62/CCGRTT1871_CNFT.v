//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
module CCGRTT1871_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73;

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
	and (d12, d7, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, x3);
	or (d17, d18, d19);
	and (d18, x0, d4);
	or (d19, d20, d21);
	and (d20, x0, d11);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, x1, d6);
	or (d24, d25, d28);
	and (d25, x0, d26);
	and (d26, x1, d27);
	and (d27, x2, d8);
	and (d28, x0, d15);
	assign f1 = d29;
	or (d29, d10, d30);
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d27);
	or (d33, d34, d36);
	and (d34, d3, d35);
	and (d35, d5, d16);
	or (d36, d37, d38);
	and (d37, d3, d23);
	or (d38, d39, d41);
	and (d39, d3, d40);
	and (d40, x1, d12);
	or (d41, d42, d43);
	and (d42, d3, d26);
	or (d43, d20, d44);
	or (d44, d45, d46);
	and (d45, x0, d32);
	or (d46, d22, d47);
	and (d47, x0, d35);
	assign f2 = d48;
	or (d48, d2, d49);
	or (d49, d31, d50);
	or (d50, d37, d51);
	or (d51, d42, d52);
	or (d52, d18, d53);
	or (d53, d45, d54);
	or (d54, d47, d55);
	or (d55, d24, d56);
	and (d56, x0, d40);
	assign f3 = d57;
	or (d57, d2, d58);
	or (d58, d37, d59);
	or (d59, d39, d60);
	or (d60, d42, d61);
	or (d61, d14, d62);
	or (d62, d18, d63);
	or (d63, d20, d64);
	or (d64, d47, d56);
	assign f4 = d65;
	or (d65, d10, d66);
	or (d66, d37, d67);
	or (d67, d42, d68);
	or (d68, d18, d69);
	or (d69, d25, d47);
	assign f5 = d70;
	or (d70, d2, d71);
	or (d71, d31, d72);
	or (d72, d42, d73);
	or (d73, d45, d56);
endmodule
