//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3)
//f4 = (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1854_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75;

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
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, d7, x3);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d12);
	or (d23, d24, d25);
	and (d24, x0, d4);
	or (d25, d26, d29);
	and (d26, x0, d27);
	and (d27, d5, d28);
	and (d28, x2, d8);
	or (d29, d30, d31);
	and (d30, x0, d15);
	and (d31, x0, d22);
	assign f1 = d32;
	or (d32, d2, d33);
	or (d33, d34, d36);
	and (d34, d3, d35);
	and (d35, d5, d19);
	or (d36, d37, d39);
	and (d37, d3, d38);
	and (d38, x1, d28);
	or (d39, d26, d40);
	or (d40, d31, d41);
	and (d41, x0, d38);
	assign f2 = d42;
	or (d42, d2, d43);
	or (d43, d34, d44);
	or (d44, d45, d46);
	and (d45, d3, d27);
	or (d46, d10, d47);
	or (d47, d37, d48);
	or (d48, d21, d49);
	or (d49, d24, d50);
	or (d50, d26, d51);
	or (d51, d41, d52);
	and (d52, x0, d11);
	assign f3 = d53;
	or (d53, d45, d54);
	or (d54, d10, d55);
	or (d55, d17, d56);
	or (d56, d52, d57);
	and (d57, x0, d35);
	assign f4 = d58;
	or (d58, d37, d59);
	or (d59, d21, d60);
	or (d60, d24, d61);
	or (d61, d57, d62);
	or (d62, d52, d63);
	or (d63, d30, d64);
	or (d64, d41, d65);
	and (d65, x0, d18);
	assign f5 = d66;
	or (d66, d2, d67);
	or (d67, d45, d68);
	or (d68, d10, d69);
	or (d69, d17, d70);
	or (d70, d37, d71);
	or (d71, d21, d72);
	or (d72, d57, d73);
	or (d73, d26, d74);
	or (d74, d52, d75);
	or (d75, d40, d65);
endmodule
