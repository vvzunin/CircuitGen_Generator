//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
module CCGRTT1910_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84;

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
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, d7, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d12);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, x2, x3);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, d5, d16);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, x1, d6);
	and (d32, x0, d22);
	assign f1 = d33;
	or (d33, d34, d35);
	and (d34, d3, d28);
	or (d35, d14, d36);
	or (d36, d21, d37);
	or (d37, d25, d38);
	or (d38, d27, d39);
	or (d39, d40, d41);
	and (d40, x0, d11);
	or (d41, d30, d42);
	or (d42, d43, d44);
	and (d43, x0, d15);
	or (d44, d32, d45);
	and (d45, x0, d19);
	assign f2 = d46;
	or (d46, d2, d47);
	or (d47, d10, d48);
	or (d48, d49, d50);
	and (d49, d3, d31);
	or (d50, d25, d51);
	or (d51, d40, d52);
	or (d52, d32, d53);
	and (d53, x0, d54);
	and (d54, d5, d23);
	assign f3 = d55;
	or (d55, d2, d56);
	or (d56, d10, d57);
	or (d57, d58, d59);
	and (d58, d3, d54);
	or (d59, d14, d60);
	or (d60, d21, d61);
	or (d61, d27, d62);
	or (d62, d53, d63);
	or (d63, d30, d44);
	assign f4 = d64;
	or (d64, d10, d65);
	or (d65, d58, d66);
	or (d66, d49, d67);
	or (d67, d14, d68);
	or (d68, d18, d69);
	or (d69, d21, d70);
	or (d70, d25, d71);
	or (d71, d53, d72);
	or (d72, d30, d73);
	or (d73, d32, d43);
	assign f5 = d74;
	or (d74, d34, d75);
	or (d75, d10, d76);
	or (d76, d49, d77);
	or (d77, d14, d78);
	or (d78, d21, d79);
	or (d79, d27, d63);
	assign f6 = d80;
	or (d80, d49, d81);
	or (d81, d18, d82);
	or (d82, d21, d83);
	or (d83, d25, d84);
	or (d84, d30, d43);
endmodule
