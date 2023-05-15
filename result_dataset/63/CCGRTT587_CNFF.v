//f0 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT587_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x2, d10);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d4, d14);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d15);
	and (d27, d28, d29);
	or (d28, d3, d25);
	and (d29, d30, d31);
	or (d30, d13, d25);
	and (d31, d32, d33);
	or (d32, d18, d25);
	or (d33, d25, d34);
	or (d34, d9, d14);
	assign f1 = d35;
	and (d35, d2, d36);
	and (d36, d7, d37);
	and (d37, d12, d38);
	and (d38, d17, d39);
	and (d39, d40, d41);
	or (d40, x0, d34);
	and (d41, d30, d32);
	assign f2 = d42;
	and (d42, d43, d44);
	or (d43, x0, d26);
	and (d44, d45, d47);
	or (d45, x0, d46);
	or (d46, x1, d19);
	and (d47, d2, d48);
	and (d48, d7, d49);
	and (d49, d12, d50);
	and (d50, d17, d51);
	and (d51, d52, d53);
	or (d52, d25, d46);
	and (d53, d28, d54);
	and (d54, d32, d55);
	or (d55, d8, d25);
	assign f3 = d56;
	and (d56, d43, d57);
	and (d57, d45, d58);
	and (d58, d7, d59);
	and (d59, d12, d60);
	and (d60, d31, d55);
	assign f4 = d61;
	and (d61, d2, d62);
	and (d62, d21, d63);
	and (d63, d52, d64);
	and (d64, d32, d65);
	or (d65, d22, d25);
	assign f5 = d66;
	and (d66, d43, d67);
	and (d67, d2, d68);
	and (d68, d7, d69);
	and (d69, d12, d70);
	and (d70, d17, d71);
	and (d71, d21, d72);
	and (d72, d40, d73);
	and (d73, d24, d74);
	and (d74, d52, d75);
	and (d75, d55, d76);
	and (d76, d30, d77);
	and (d77, d33, d65);
	assign f6 = d78;
	and (d78, d45, d79);
	and (d79, d12, d80);
	and (d80, d17, d81);
	and (d81, d21, d82);
	and (d82, d40, d83);
	and (d83, d41, d55);
endmodule
