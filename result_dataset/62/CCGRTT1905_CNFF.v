//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1905_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84, d85, d86;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x2, d9);
	not (d9, x3);
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d13, d18);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, d18, d25);
	or (d25, d9, d14);
	and (d26, d27, d29);
	or (d27, d7, d28);
	not (d28, x0);
	and (d29, d30, d32);
	or (d30, d28, d31);
	or (d31, x1, d25);
	or (d32, d28, d33);
	or (d33, d8, d18);
	assign f1 = d34;
	and (d34, d6, d35);
	and (d35, d36, d37);
	or (d36, x0, d31);
	and (d37, d38, d39);
	or (d38, x0, d33);
	and (d39, d20, d40);
	and (d40, d23, d41);
	and (d41, d42, d43);
	or (d42, d3, d28);
	and (d43, d44, d45);
	or (d44, d17, d28);
	or (d45, d21, d28);
	assign f2 = d46;
	and (d46, d6, d47);
	and (d47, d11, d48);
	and (d48, d36, d49);
	and (d49, d16, d50);
	and (d50, d42, d51);
	and (d51, d32, d52);
	and (d52, d45, d53);
	or (d53, d24, d28);
	assign f3 = d54;
	and (d54, d2, d55);
	and (d55, d11, d56);
	and (d56, d36, d57);
	and (d57, d16, d58);
	and (d58, d20, d59);
	and (d59, d23, d60);
	and (d60, d27, d61);
	and (d61, d30, d53);
	assign f4 = d62;
	and (d62, d2, d63);
	and (d63, d6, d64);
	and (d64, d11, d65);
	and (d65, d36, d66);
	and (d66, d20, d67);
	and (d67, d23, d68);
	and (d68, d42, d69);
	and (d69, d27, d70);
	and (d70, d29, d71);
	or (d71, d12, d28);
	assign f5 = d72;
	and (d72, d6, d73);
	and (d73, d16, d74);
	and (d74, d38, d75);
	and (d75, d23, d76);
	and (d76, d42, d77);
	and (d77, d27, d78);
	and (d78, d43, d71);
	assign f6 = d79;
	and (d79, d2, d80);
	and (d80, d6, d81);
	and (d81, d11, d82);
	and (d82, d36, d83);
	and (d83, d20, d84);
	and (d84, d42, d85);
	and (d85, d71, d86);
	and (d86, d32, d44);
endmodule
