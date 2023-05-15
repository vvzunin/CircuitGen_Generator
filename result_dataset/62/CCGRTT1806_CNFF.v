//f0 = (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1806_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, d6);
	not (d5, x2);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, d9, d10);
	not (d9, x0);
	or (d10, x1, d11);
	or (d11, x2, d6);
	and (d12, d13, d14);
	or (d13, d3, d9);
	or (d14, d9, d15);
	or (d15, d4, d16);
	not (d16, x1);
	assign f1 = d17;
	and (d17, d18, d21);
	or (d18, x0, d19);
	or (d19, x1, d20);
	or (d20, x2, x3);
	and (d21, d22, d23);
	or (d22, x0, d10);
	and (d23, d24, d27);
	or (d24, x0, d25);
	or (d25, x1, d26);
	or (d26, d5, x3);
	and (d27, d28, d30);
	or (d28, x0, d29);
	or (d29, d11, d16);
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, d16, d26);
	and (d33, d34, d35);
	or (d34, x0, d15);
	and (d35, d8, d36);
	and (d36, d13, d37);
	or (d37, d9, d38);
	or (d38, d16, d20);
	assign f2 = d39;
	and (d39, d18, d40);
	and (d40, d22, d41);
	and (d41, d24, d42);
	and (d42, d43, d44);
	or (d43, x0, d38);
	and (d44, d31, d45);
	and (d45, d46, d47);
	or (d46, d9, d19);
	and (d47, d8, d48);
	and (d48, d49, d50);
	or (d49, d9, d25);
	and (d50, d13, d51);
	and (d51, d37, d52);
	and (d52, d14, d53);
	or (d53, d9, d29);
	assign f3 = d54;
	and (d54, d18, d55);
	and (d55, d22, d56);
	and (d56, d24, d57);
	and (d57, d2, d58);
	and (d58, d43, d59);
	and (d59, d28, d60);
	and (d60, d31, d61);
	and (d61, d8, d62);
	and (d62, d37, d63);
	or (d63, d9, d32);
	assign f4 = d64;
	and (d64, d18, d65);
	and (d65, d22, d66);
	and (d66, d24, d67);
	and (d67, d28, d68);
	and (d68, d31, d69);
	and (d69, d36, d49);
	assign f5 = d70;
	and (d70, d18, d71);
	and (d71, d2, d72);
	and (d72, d28, d73);
	and (d73, d34, d74);
	and (d74, d46, d75);
	and (d75, d8, d76);
	and (d76, d49, d77);
	and (d77, d53, d63);
endmodule
