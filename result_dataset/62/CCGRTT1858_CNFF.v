//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1858_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

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
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d13, d17);
	or (d17, x3, d18);
	not (d18, x2);
	and (d19, d20, d22);
	or (d20, d7, d21);
	not (d21, x0);
	and (d22, d23, d25);
	or (d23, d21, d24);
	or (d24, x1, d17);
	and (d25, d26, d27);
	or (d26, d12, d21);
	and (d27, d28, d30);
	or (d28, d21, d29);
	or (d29, d8, d13);
	and (d30, d31, d32);
	or (d31, d16, d21);
	or (d32, d21, d33);
	or (d33, d13, d34);
	or (d34, d9, d18);
	assign f1 = d35;
	and (d35, d2, d36);
	and (d36, d6, d37);
	and (d37, d38, d39);
	or (d38, x0, d24);
	and (d39, d40, d42);
	or (d40, x0, d41);
	or (d41, x1, d34);
	and (d42, d11, d43);
	and (d43, d15, d44);
	and (d44, d45, d46);
	or (d45, d3, d21);
	and (d46, d20, d47);
	and (d47, d48, d49);
	or (d48, d21, d41);
	and (d49, d26, d50);
	and (d50, d28, d31);
	assign f2 = d51;
	and (d51, d38, d52);
	and (d52, d40, d53);
	and (d53, d45, d54);
	and (d54, d48, d55);
	and (d55, d28, d32);
	assign f3 = d56;
	and (d56, d2, d57);
	and (d57, d6, d58);
	and (d58, d59, d60);
	or (d59, x0, d29);
	and (d60, d61, d62);
	or (d61, x0, d33);
	and (d62, d20, d63);
	and (d63, d23, d64);
	and (d64, d28, d48);
	assign f4 = d65;
	and (d65, d2, d66);
	and (d66, d6, d67);
	and (d67, d38, d68);
	and (d68, d15, d69);
	and (d69, d61, d70);
	and (d70, d20, d71);
	and (d71, d23, d32);
	assign f5 = d72;
	and (d72, d6, d73);
	and (d73, d38, d74);
	and (d74, d11, d75);
	and (d75, d15, d76);
	and (d76, d45, d77);
	and (d77, d20, d78);
	and (d78, d26, d30);
endmodule
