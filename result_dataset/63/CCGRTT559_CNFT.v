//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT559_CNFT(
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
	and (d12, x2, d8);
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d6);
	or (d16, d17, d18);
	and (d17, x0, d11);
	or (d18, d19, d22);
	and (d19, x0, d20);
	and (d20, d5, d21);
	and (d21, x2, x3);
	or (d22, d23, d26);
	and (d23, x0, d24);
	and (d24, x1, d25);
	and (d25, d7, x3);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d12);
	and (d29, x0, d30);
	and (d30, x1, d21);
	assign f1 = d31;
	or (d31, d32, d34);
	and (d32, d3, d33);
	and (d33, d5, d25);
	or (d34, d35, d36);
	and (d35, d3, d20);
	or (d36, d37, d38);
	and (d37, d3, d24);
	or (d38, d39, d40);
	and (d39, d3, d28);
	or (d40, d41, d42);
	and (d41, x0, d33);
	or (d42, d17, d23);
	assign f2 = d43;
	or (d43, d2, d44);
	or (d44, d10, d45);
	or (d45, d35, d46);
	or (d46, d37, d47);
	or (d47, d39, d48);
	or (d48, d49, d50);
	and (d49, d3, d30);
	or (d50, d51, d52);
	and (d51, x0, d4);
	or (d52, d19, d53);
	and (d53, x0, d15);
	assign f3 = d54;
	or (d54, d10, d55);
	or (d55, d37, d56);
	or (d56, d39, d57);
	or (d57, d49, d58);
	or (d58, d51, d59);
	or (d59, d41, d60);
	or (d60, d22, d53);
	assign f4 = d61;
	or (d61, d2, d62);
	or (d62, d32, d63);
	or (d63, d10, d64);
	or (d64, d35, d65);
	or (d65, d14, d66);
	or (d66, d39, d67);
	or (d67, d41, d68);
	or (d68, d17, d69);
	or (d69, d19, d26);
	assign f5 = d70;
	or (d70, d32, d71);
	or (d71, d10, d72);
	or (d72, d49, d73);
	or (d73, d16, d51);
endmodule
