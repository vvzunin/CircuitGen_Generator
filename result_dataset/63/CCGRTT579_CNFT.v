//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT579_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d12);
	and (d10, d3, d11);
	and (d11, x1, d6);
	or (d12, d13, d16);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, d7, x3);
	or (d16, d17, d18);
	and (d17, x0, d4);
	or (d18, d19, d21);
	and (d19, x0, d20);
	and (d20, d5, d15);
	or (d21, d22, d25);
	and (d22, x0, d23);
	and (d23, d5, d24);
	and (d24, x2, x3);
	or (d25, d26, d27);
	and (d26, x0, d11);
	and (d27, x0, d28);
	and (d28, x1, d29);
	and (d29, x2, d8);
	assign f1 = d30;
	or (d30, d13, d31);
	or (d31, d32, d33);
	and (d32, d3, d28);
	or (d33, d19, d34);
	or (d34, d22, d35);
	or (d35, d26, d36);
	or (d36, d37, d38);
	and (d37, x0, d14);
	and (d38, x0, d39);
	and (d39, x1, d24);
	assign f2 = d40;
	or (d40, d41, d42);
	and (d41, d3, d20);
	or (d42, d43, d45);
	and (d43, d3, d44);
	and (d44, d5, d29);
	or (d45, d46, d47);
	and (d46, d3, d23);
	or (d47, d48, d49);
	and (d48, d3, d39);
	or (d49, d26, d50);
	or (d50, d27, d38);
	assign f3 = d51;
	or (d51, d41, d52);
	or (d52, d43, d53);
	or (d53, d46, d54);
	or (d54, d13, d55);
	or (d55, d48, d56);
	or (d56, d17, d57);
	or (d57, d19, d58);
	or (d58, d59, d60);
	and (d59, x0, d44);
	or (d60, d22, d61);
	or (d61, d27, d37);
	assign f4 = d62;
	or (d62, d43, d63);
	or (d63, d46, d64);
	or (d64, d10, d65);
	or (d65, d32, d66);
	or (d66, d19, d67);
	or (d67, d35, d59);
	assign f5 = d68;
	or (d68, d2, d69);
	or (d69, d41, d70);
	or (d70, d46, d71);
	or (d71, d32, d72);
	or (d72, d48, d73);
	or (d73, d59, d74);
	or (d74, d26, d61);
	assign f6 = d75;
	or (d75, d2, d76);
	or (d76, d43, d77);
	or (d77, d46, d78);
	or (d78, d48, d79);
	or (d79, d17, d80);
	or (d80, d19, d81);
	or (d81, d36, d59);
endmodule
