//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1713_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

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
	and (d15, d5, d16);
	and (d16, x2, d8);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d12);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d16);
	or (d23, d24, d27);
	and (d24, d3, d25);
	and (d25, x1, d26);
	and (d26, x2, x3);
	or (d27, d28, d29);
	and (d28, x0, d11);
	or (d29, d30, d31);
	and (d30, x0, d15);
	or (d31, d32, d34);
	and (d32, x0, d33);
	and (d33, d5, d26);
	or (d34, d35, d37);
	and (d35, x0, d36);
	and (d36, x1, d6);
	or (d37, d38, d39);
	and (d38, x0, d19);
	and (d39, x0, d22);
	assign f1 = d40;
	or (d40, d2, d41);
	or (d41, d14, d42);
	or (d42, d43, d44);
	and (d43, d3, d33);
	or (d44, d45, d46);
	and (d45, d3, d36);
	or (d46, d21, d47);
	or (d47, d24, d48);
	or (d48, d28, d49);
	or (d49, d30, d50);
	or (d50, d32, d51);
	and (d51, x0, d25);
	assign f2 = d52;
	or (d52, d10, d53);
	or (d53, d14, d54);
	or (d54, d43, d55);
	or (d55, d18, d56);
	or (d56, d21, d57);
	or (d57, d24, d58);
	or (d58, d39, d59);
	and (d59, x0, d4);
	assign f3 = d60;
	or (d60, d2, d61);
	or (d61, d10, d62);
	or (d62, d14, d63);
	or (d63, d21, d64);
	or (d64, d59, d65);
	or (d65, d28, d66);
	or (d66, d30, d67);
	or (d67, d32, d68);
	or (d68, d38, d51);
	assign f4 = d69;
	or (d69, d10, d70);
	or (d70, d14, d71);
	or (d71, d43, d72);
	or (d72, d28, d31);
endmodule
