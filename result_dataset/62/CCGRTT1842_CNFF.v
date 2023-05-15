//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1842_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d14);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d9, d14);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, d14, d25);
	or (d25, d5, d10);
	and (d26, d27, d30);
	or (d27, d28, d29);
	not (d28, x0);
	or (d29, x1, d15);
	and (d30, d31, d32);
	or (d31, d3, d28);
	and (d32, d33, d34);
	or (d33, d13, d28);
	or (d34, d24, d28);
	assign f1 = d35;
	and (d35, d36, d37);
	or (d36, x0, d29);
	and (d37, d7, d38);
	and (d38, d39, d41);
	or (d39, x0, d40);
	or (d40, x1, d25);
	and (d41, d12, d42);
	and (d42, d20, d43);
	and (d43, d44, d45);
	or (d44, d28, d40);
	and (d45, d33, d46);
	and (d46, d34, d47);
	or (d47, d21, d28);
	assign f2 = d48;
	and (d48, d36, d49);
	and (d49, d2, d50);
	and (d50, d12, d51);
	and (d51, d23, d52);
	and (d52, d27, d53);
	and (d53, d31, d54);
	and (d54, d33, d47);
	assign f3 = d55;
	and (d55, d36, d56);
	and (d56, d39, d57);
	and (d57, d12, d58);
	and (d58, d23, d59);
	and (d59, d27, d60);
	and (d60, d31, d61);
	and (d61, d62, d63);
	or (d62, d8, d28);
	and (d63, d32, d44);
	assign f4 = d64;
	and (d64, d7, d65);
	and (d65, d12, d66);
	and (d66, d20, d67);
	and (d67, d23, d68);
	and (d68, d27, d62);
	assign f5 = d69;
	and (d69, d36, d70);
	and (d70, d2, d71);
	and (d71, d12, d72);
	and (d72, d17, d73);
	and (d73, d23, d74);
	and (d74, d27, d75);
	and (d75, d44, d76);
	and (d76, d33, d77);
	and (d77, d46, d78);
	or (d78, d18, d28);
endmodule
