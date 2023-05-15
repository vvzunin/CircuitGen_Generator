//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT545_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79;

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
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, d7, x3);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d12);
	or (d23, d24, d27);
	and (d24, d3, d25);
	and (d25, x1, d26);
	and (d26, x2, x3);
	or (d27, d28, d29);
	and (d28, x0, d4);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, d5, d19);
	and (d32, x0, d18);
	assign f1 = d33;
	or (d33, d2, d34);
	or (d34, d10, d35);
	or (d35, d17, d36);
	or (d36, d21, d37);
	or (d37, d24, d38);
	or (d38, d28, d39);
	or (d39, d30, d40);
	or (d40, d41, d43);
	and (d41, x0, d42);
	and (d42, d5, d26);
	or (d43, d44, d45);
	and (d44, x0, d15);
	or (d45, d32, d46);
	and (d46, x0, d25);
	assign f2 = d47;
	or (d47, d48, d49);
	and (d48, d3, d31);
	or (d49, d10, d50);
	or (d50, d51, d52);
	and (d51, d3, d42);
	or (d52, d14, d53);
	or (d53, d21, d54);
	or (d54, d30, d55);
	or (d55, d56, d57);
	and (d56, x0, d11);
	or (d57, d32, d58);
	or (d58, d46, d59);
	and (d59, x0, d22);
	assign f3 = d60;
	or (d60, d2, d61);
	or (d61, d48, d62);
	or (d62, d10, d63);
	or (d63, d17, d64);
	or (d64, d21, d65);
	or (d65, d24, d66);
	or (d66, d56, d67);
	or (d67, d32, d41);
	assign f4 = d68;
	or (d68, d10, d69);
	or (d69, d51, d70);
	or (d70, d14, d71);
	or (d71, d44, d58);
	assign f5 = d72;
	or (d72, d2, d73);
	or (d73, d10, d74);
	or (d74, d51, d75);
	or (d75, d14, d76);
	or (d76, d17, d77);
	or (d77, d30, d78);
	or (d78, d41, d79);
	or (d79, d44, d46);
endmodule
