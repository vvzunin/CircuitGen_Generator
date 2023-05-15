//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT586_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84, d85, d86;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, d9, d10);
	not (d9, x2);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, d10);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x3, d9);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d8, d14);
	and (d23, d24, d26);
	or (d24, d3, d25);
	not (d25, x0);
	and (d26, d27, d29);
	or (d27, d25, d28);
	or (d28, x1, d19);
	and (d29, d30, d32);
	or (d30, d25, d31);
	or (d31, d4, d14);
	or (d32, d22, d25);
	assign f1 = d33;
	and (d33, d2, d34);
	and (d34, d35, d36);
	or (d35, x0, d31);
	and (d36, d12, d37);
	and (d37, d17, d38);
	and (d38, d21, d39);
	and (d39, d24, d40);
	and (d40, d27, d41);
	and (d41, d30, d42);
	or (d42, d7, d25);
	assign f2 = d43;
	and (d43, d2, d44);
	and (d44, d45, d46);
	or (d45, x0, d28);
	and (d46, d6, d47);
	and (d47, d35, d48);
	and (d48, d12, d49);
	and (d49, d17, d50);
	and (d50, d21, d51);
	and (d51, d24, d52);
	and (d52, d53, d55);
	or (d53, d25, d54);
	or (d54, x1, d15);
	and (d55, d32, d42);
	assign f3 = d56;
	and (d56, d2, d57);
	and (d57, d45, d58);
	and (d58, d17, d59);
	and (d59, d24, d60);
	and (d60, d42, d61);
	and (d61, d32, d62);
	or (d62, d13, d25);
	assign f4 = d63;
	and (d63, d2, d64);
	and (d64, d45, d65);
	and (d65, d6, d66);
	and (d66, d35, d67);
	and (d67, d21, d68);
	and (d68, d24, d69);
	and (d69, d32, d53);
	assign f5 = d70;
	and (d70, d2, d71);
	and (d71, d72, d73);
	or (d72, x0, d54);
	and (d73, d45, d74);
	and (d74, d17, d75);
	and (d75, d21, d76);
	and (d76, d62, d77);
	and (d77, d32, d78);
	or (d78, d18, d25);
	assign f6 = d79;
	and (d79, d72, d80);
	and (d80, d6, d81);
	and (d81, d17, d82);
	and (d82, d21, d83);
	and (d83, d24, d84);
	and (d84, d53, d85);
	and (d85, d42, d86);
	and (d86, d30, d76);
endmodule
