//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1892_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

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
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, d7, d12);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d6);
	or (d24, d25, d27);
	and (d25, d3, d26);
	and (d26, x1, d11);
	or (d27, d28, d30);
	and (d28, d3, d29);
	and (d29, x1, d16);
	or (d30, d31, d33);
	and (d31, x0, d32);
	and (d32, d5, d20);
	or (d33, d34, d35);
	and (d34, x0, d4);
	or (d35, d36, d37);
	and (d36, x0, d15);
	or (d37, d38, d39);
	and (d38, x0, d23);
	and (d39, x0, d26);
	assign f1 = d40;
	or (d40, d41, d42);
	and (d41, d3, d32);
	or (d42, d9, d43);
	or (d43, d14, d44);
	or (d44, d18, d45);
	or (d45, d31, d46);
	or (d46, d47, d48);
	and (d47, x0, d10);
	or (d48, d38, d49);
	or (d49, d39, d50);
	and (d50, x0, d29);
	assign f2 = d51;
	or (d51, d9, d52);
	or (d52, d18, d53);
	or (d53, d25, d54);
	or (d54, d34, d55);
	or (d55, d47, d56);
	or (d56, d36, d48);
	assign f3 = d57;
	or (d57, d41, d58);
	or (d58, d2, d59);
	or (d59, d22, d60);
	or (d60, d25, d61);
	or (d61, d28, d62);
	or (d62, d31, d63);
	or (d63, d36, d50);
	assign f4 = d64;
	or (d64, d41, d65);
	or (d65, d14, d66);
	or (d66, d18, d67);
	or (d67, d25, d68);
	or (d68, d36, d69);
	or (d69, d37, d70);
	and (d70, x0, d19);
	assign f5 = d71;
	or (d71, d14, d72);
	or (d72, d22, d73);
	or (d73, d25, d74);
	or (d74, d28, d75);
	or (d75, d31, d76);
	or (d76, d47, d77);
	or (d77, d70, d78);
	or (d78, d38, d50);
endmodule
