//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1825_CNFT(
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
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d16);
	or (d23, d24, d25);
	and (d24, x0, d4);
	or (d25, d26, d27);
	and (d26, x0, d11);
	and (d27, x0, d19);
	assign f1 = d28;
	or (d28, d2, d29);
	or (d29, d14, d30);
	or (d30, d18, d31);
	or (d31, d32, d33);
	and (d32, x0, d15);
	or (d33, d27, d34);
	or (d34, d35, d37);
	and (d35, x0, d36);
	and (d36, x1, d12);
	and (d37, x0, d22);
	assign f2 = d38;
	or (d38, d10, d39);
	or (d39, d14, d40);
	or (d40, d18, d41);
	or (d41, d42, d43);
	and (d42, d3, d36);
	or (d43, d26, d44);
	or (d44, d35, d45);
	or (d45, d37, d46);
	and (d46, x0, d47);
	and (d47, x1, d48);
	and (d48, x2, d8);
	assign f3 = d49;
	or (d49, d2, d50);
	or (d50, d10, d51);
	or (d51, d14, d52);
	or (d52, d18, d53);
	or (d53, d54, d55);
	and (d54, d3, d47);
	or (d55, d21, d56);
	or (d56, d24, d57);
	or (d57, d26, d58);
	or (d58, d37, d59);
	and (d59, x0, d60);
	and (d60, d5, d48);
	assign f4 = d61;
	or (d61, d10, d62);
	or (d62, d63, d64);
	and (d63, d3, d60);
	or (d64, d54, d65);
	or (d65, d24, d66);
	or (d66, d27, d44);
	assign f5 = d67;
	or (d67, d10, d68);
	or (d68, d63, d69);
	or (d69, d18, d70);
	or (d70, d42, d71);
	or (d71, d54, d72);
	or (d72, d21, d73);
	or (d73, d27, d45);
endmodule
