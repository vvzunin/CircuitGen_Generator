//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1872_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d13);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, d12);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, d7, d12);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d11);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d23, d24);
	and (d23, x0, d10);
	or (d24, d25, d26);
	and (d25, x0, d15);
	or (d26, d27, d28);
	and (d27, x0, d19);
	and (d28, x0, d29);
	and (d29, x1, d30);
	and (d30, x2, x3);
	assign f1 = d31;
	or (d31, d32, d34);
	and (d32, d3, d33);
	and (d33, d5, d16);
	or (d34, d2, d35);
	or (d35, d9, d36);
	or (d36, d37, d39);
	and (d37, d3, d38);
	and (d38, d5, d30);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, x1, d6);
	or (d42, d43, d44);
	and (d43, d3, d29);
	or (d44, d45, d46);
	and (d45, x0, d33);
	or (d46, d23, d47);
	or (d47, d24, d48);
	and (d48, x0, d38);
	assign f2 = d49;
	or (d49, d32, d50);
	or (d50, d37, d51);
	or (d51, d40, d52);
	or (d52, d18, d53);
	or (d53, d45, d54);
	or (d54, d21, d55);
	or (d55, d23, d56);
	or (d56, d27, d57);
	and (d57, x0, d41);
	assign f3 = d58;
	or (d58, d9, d59);
	or (d59, d40, d60);
	or (d60, d45, d61);
	or (d61, d21, d62);
	or (d62, d26, d57);
	assign f4 = d63;
	or (d63, d40, d64);
	or (d64, d43, d65);
	or (d65, d45, d66);
	or (d66, d21, d67);
	or (d67, d48, d62);
	assign f5 = d68;
	or (d68, d32, d69);
	or (d69, d40, d70);
	or (d70, d21, d71);
	or (d71, d23, d26);
endmodule
