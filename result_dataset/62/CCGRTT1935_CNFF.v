//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1935_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x3, d10);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d9, d14);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d15);
	and (d27, d28, d30);
	or (d28, d25, d29);
	or (d29, x1, d19);
	and (d30, d31, d32);
	or (d31, d13, d25);
	and (d32, d33, d34);
	or (d33, d18, d25);
	or (d34, d22, d25);
	assign f1 = d35;
	and (d35, d2, d36);
	and (d36, d37, d38);
	or (d37, x0, d29);
	and (d38, d12, d39);
	and (d39, d40, d42);
	or (d40, x0, d41);
	or (d41, d4, d14);
	and (d42, d24, d43);
	and (d43, d31, d44);
	or (d44, d8, d25);
	assign f2 = d45;
	and (d45, d46, d47);
	or (d46, x0, d26);
	and (d47, d37, d48);
	and (d48, d40, d49);
	and (d49, d21, d50);
	and (d50, d28, d31);
	assign f3 = d51;
	and (d51, d46, d52);
	and (d52, d2, d53);
	and (d53, d37, d54);
	and (d54, d7, d55);
	and (d55, d12, d56);
	and (d56, d40, d57);
	and (d57, d17, d58);
	and (d58, d24, d59);
	and (d59, d28, d60);
	and (d60, d44, d61);
	and (d61, d31, d34);
	assign f4 = d62;
	and (d62, d46, d63);
	and (d63, d7, d64);
	and (d64, d40, d65);
	and (d65, d17, d66);
	and (d66, d21, d67);
	and (d67, d24, d68);
	and (d68, d69, d70);
	or (d69, d3, d25);
	and (d70, d28, d71);
	and (d71, d33, d72);
	or (d72, d25, d41);
	assign f5 = d73;
	and (d73, d7, d74);
	and (d74, d12, d75);
	and (d75, d40, d76);
	and (d76, d17, d77);
	and (d77, d24, d78);
	and (d78, d34, d72);
	assign f6 = d79;
	and (d79, d2, d80);
	and (d80, d7, d81);
	and (d81, d21, d82);
	and (d82, d24, d83);
	and (d83, d28, d72);
endmodule
