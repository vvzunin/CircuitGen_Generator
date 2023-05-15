//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1889_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76;

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
	and (d23, x1, d6);
	or (d24, d25, d27);
	and (d25, d3, d26);
	and (d26, x1, d16);
	or (d27, d28, d30);
	and (d28, d3, d29);
	and (d29, x1, d20);
	or (d30, d31, d32);
	and (d31, x0, d11);
	or (d32, d33, d34);
	and (d33, x0, d15);
	and (d34, x0, d29);
	assign f1 = d35;
	or (d35, d2, d36);
	or (d36, d14, d37);
	or (d37, d18, d38);
	or (d38, d22, d39);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, x1, d12);
	or (d42, d25, d43);
	or (d43, d44, d45);
	and (d44, x0, d4);
	or (d45, d31, d46);
	or (d46, d33, d47);
	or (d47, d48, d49);
	and (d48, x0, d23);
	and (d49, x0, d26);
	assign f2 = d50;
	or (d50, d2, d51);
	or (d51, d18, d52);
	or (d52, d22, d53);
	or (d53, d40, d54);
	or (d54, d25, d55);
	or (d55, d28, d56);
	or (d56, d44, d57);
	or (d57, d33, d49);
	assign f3 = d58;
	or (d58, d2, d59);
	or (d59, d10, d60);
	or (d60, d22, d61);
	or (d61, d33, d44);
	assign f4 = d62;
	or (d62, d14, d63);
	or (d63, d18, d64);
	or (d64, d22, d65);
	or (d65, d25, d66);
	or (d66, d28, d67);
	or (d67, d68, d69);
	and (d68, x0, d19);
	or (d69, d34, d49);
	assign f5 = d70;
	or (d70, d10, d71);
	or (d71, d14, d72);
	or (d72, d40, d73);
	or (d73, d28, d74);
	or (d74, d33, d75);
	or (d75, d68, d76);
	or (d76, d48, d69);
endmodule
