//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1928_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84, d85;

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
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, x2, d8);
	or (d21, d22, d23);
	and (d22, x0, d4);
	or (d23, d24, d25);
	and (d24, x0, d15);
	or (d25, d26, d28);
	and (d26, x0, d27);
	and (d27, x1, d6);
	and (d28, x0, d29);
	and (d29, x1, d12);
	assign f1 = d30;
	or (d30, d2, d31);
	or (d31, d32, d33);
	and (d32, d3, d27);
	or (d33, d34, d35);
	and (d34, d3, d29);
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, x1, d16);
	or (d38, d22, d39);
	or (d39, d40, d41);
	and (d40, x0, d11);
	or (d41, d25, d42);
	and (d42, x0, d43);
	and (d43, d5, d20);
	assign f2 = d44;
	or (d44, d2, d45);
	or (d45, d10, d46);
	or (d46, d47, d48);
	and (d47, d3, d43);
	or (d48, d14, d49);
	or (d49, d34, d50);
	or (d50, d18, d51);
	or (d51, d36, d52);
	or (d52, d42, d53);
	or (d53, d24, d54);
	or (d54, d55, d56);
	and (d55, x0, d19);
	and (d56, x0, d37);
	assign f3 = d57;
	or (d57, d47, d58);
	or (d58, d32, d59);
	or (d59, d34, d60);
	or (d60, d18, d61);
	or (d61, d22, d62);
	or (d62, d42, d63);
	or (d63, d24, d55);
	assign f4 = d64;
	or (d64, d2, d65);
	or (d65, d47, d66);
	or (d66, d14, d67);
	or (d67, d34, d68);
	or (d68, d22, d69);
	or (d69, d42, d70);
	or (d70, d24, d71);
	or (d71, d26, d54);
	assign f5 = d72;
	or (d72, d14, d73);
	or (d73, d34, d74);
	or (d74, d36, d75);
	or (d75, d42, d76);
	or (d76, d26, d77);
	or (d77, d28, d55);
	assign f6 = d78;
	or (d78, d2, d79);
	or (d79, d47, d80);
	or (d80, d32, d81);
	or (d81, d18, d82);
	or (d82, d22, d83);
	or (d83, d40, d84);
	or (d84, d42, d85);
	or (d85, d24, d76);
endmodule
