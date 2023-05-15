//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1899_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d11);
	and (d9, d3, d10);
	and (d10, x1, d6);
	or (d11, d12, d16);
	and (d12, d3, d13);
	and (d13, x1, d14);
	and (d14, x2, d15);
	not (d15, x3);
	or (d16, d17, d18);
	and (d17, x0, d4);
	or (d18, d19, d21);
	and (d19, x0, d20);
	and (d20, d5, d14);
	or (d21, d22, d25);
	and (d22, x0, d23);
	and (d23, x1, d24);
	and (d24, d7, d15);
	or (d25, d26, d27);
	and (d26, x0, d13);
	and (d27, x0, d28);
	and (d28, x1, d29);
	and (d29, x2, x3);
	assign f1 = d30;
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d24);
	or (d33, d34, d35);
	and (d34, d3, d20);
	or (d35, d36, d37);
	and (d36, d3, d23);
	or (d37, d9, d38);
	or (d38, d12, d39);
	or (d39, d40, d41);
	and (d40, d3, d28);
	or (d41, d19, d42);
	or (d42, d26, d43);
	and (d43, x0, d44);
	and (d44, d5, d29);
	assign f2 = d45;
	or (d45, d31, d46);
	or (d46, d2, d47);
	or (d47, d34, d48);
	or (d48, d36, d49);
	or (d49, d9, d50);
	or (d50, d12, d51);
	or (d51, d52, d53);
	and (d52, x0, d32);
	or (d53, d19, d43);
	assign f3 = d54;
	or (d54, d31, d55);
	or (d55, d2, d56);
	or (d56, d57, d58);
	and (d57, d3, d44);
	or (d58, d9, d59);
	or (d59, d40, d60);
	or (d60, d52, d61);
	or (d61, d25, d62);
	and (d62, x0, d10);
	assign f4 = d63;
	or (d63, d31, d64);
	or (d64, d57, d65);
	or (d65, d36, d66);
	or (d66, d9, d67);
	or (d67, d40, d68);
	or (d68, d52, d69);
	or (d69, d43, d70);
	or (d70, d22, d71);
	or (d71, d26, d62);
	assign f5 = d72;
	or (d72, d57, d73);
	or (d73, d36, d74);
	or (d74, d12, d70);
endmodule
