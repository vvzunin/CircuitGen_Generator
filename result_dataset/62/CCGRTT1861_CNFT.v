//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1861_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
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
	and (d12, x2, d8);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, d7, x3);
	or (d24, d25, d26);
	and (d25, x0, d11);
	and (d26, x0, d15);
	assign f1 = d27;
	or (d27, d2, d28);
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, d5, d23);
	or (d31, d18, d32);
	and (d32, x0, d4);
	assign f2 = d33;
	or (d33, d10, d34);
	or (d34, d14, d35);
	or (d35, d21, d36);
	or (d36, d37, d39);
	and (d37, d3, d38);
	and (d38, x1, d12);
	or (d39, d40, d41);
	and (d40, x0, d30);
	or (d41, d26, d42);
	or (d42, d43, d44);
	and (d43, x0, d19);
	and (d44, x0, d45);
	and (d45, x1, d16);
	assign f3 = d46;
	or (d46, d2, d47);
	or (d47, d10, d48);
	or (d48, d18, d49);
	or (d49, d21, d50);
	or (d50, d37, d51);
	or (d51, d52, d53);
	and (d52, d3, d45);
	or (d53, d32, d39);
	assign f4 = d54;
	or (d54, d2, d55);
	or (d55, d29, d56);
	or (d56, d14, d57);
	or (d57, d18, d58);
	or (d58, d37, d59);
	or (d59, d32, d60);
	or (d60, d40, d61);
	or (d61, d43, d62);
	or (d62, d44, d63);
	and (d63, x0, d38);
	assign f5 = d64;
	or (d64, d2, d65);
	or (d65, d29, d66);
	or (d66, d10, d67);
	or (d67, d14, d68);
	or (d68, d37, d69);
	or (d69, d52, d70);
	or (d70, d40, d71);
	or (d71, d62, d72);
	and (d72, x0, d22);
endmodule
