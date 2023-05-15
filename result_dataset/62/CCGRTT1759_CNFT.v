//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3)
module CCGRTT1759_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

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
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, d5, d20);
	and (d20, x2, x3);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d12);
	or (d24, d25, d26);
	and (d25, x0, d4);
	and (d26, x0, d15);
	assign f1 = d27;
	or (d27, d10, d28);
	or (d28, d14, d29);
	or (d29, d22, d30);
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, x1, d20);
	or (d33, d25, d34);
	or (d34, d35, d36);
	and (d35, x0, d11);
	or (d36, d26, d37);
	or (d37, d38, d40);
	and (d38, x0, d39);
	and (d39, x1, d6);
	or (d40, d41, d42);
	and (d41, x0, d23);
	and (d42, x0, d32);
	assign f2 = d43;
	or (d43, d2, d44);
	or (d44, d14, d45);
	or (d45, d18, d46);
	or (d46, d47, d49);
	and (d47, d3, d48);
	and (d48, x1, d16);
	or (d49, d31, d50);
	or (d50, d35, d51);
	or (d51, d26, d52);
	or (d52, d53, d54);
	and (d53, x0, d19);
	or (d54, d38, d41);
	assign f3 = d55;
	or (d55, d14, d56);
	or (d56, d57, d58);
	and (d57, d3, d39);
	or (d58, d47, d59);
	or (d59, d25, d60);
	or (d60, d38, d61);
	or (d61, d41, d62);
	and (d62, x0, d48);
	assign f4 = d63;
	or (d63, d10, d64);
	or (d64, d14, d65);
	or (d65, d57, d66);
	or (d66, d22, d67);
	or (d67, d47, d68);
	or (d68, d25, d53);
endmodule
