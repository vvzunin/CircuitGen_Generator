//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1919_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d14, d18);
	or (d18, x2, d10);
	and (d19, d20, d22);
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d26);
	or (d23, d21, d24);
	or (d24, x1, d25);
	or (d25, x3, d9);
	and (d26, d27, d28);
	or (d27, d7, d21);
	or (d28, d13, d21);
	assign f1 = d29;
	and (d29, d2, d30);
	and (d30, d31, d32);
	or (d31, x0, d24);
	and (d32, d6, d33);
	and (d33, d12, d34);
	and (d34, d16, d35);
	and (d35, d36, d37);
	or (d36, d17, d21);
	and (d37, d38, d40);
	or (d38, d21, d39);
	or (d39, d14, d25);
	or (d40, d21, d41);
	or (d41, d8, d14);
	assign f2 = d42;
	and (d42, d31, d43);
	and (d43, d44, d45);
	or (d44, x0, d39);
	and (d45, d46, d47);
	or (d46, x0, d41);
	and (d47, d20, d48);
	and (d48, d49, d51);
	or (d49, d21, d50);
	or (d50, x1, d18);
	and (d51, d23, d52);
	and (d52, d28, d40);
	assign f3 = d53;
	and (d53, d2, d54);
	and (d54, d31, d55);
	and (d55, d12, d56);
	and (d56, d46, d57);
	and (d57, d49, d58);
	and (d58, d23, d59);
	and (d59, d27, d60);
	and (d60, d28, d38);
	assign f4 = d61;
	and (d61, d2, d62);
	and (d62, d44, d63);
	and (d63, d27, d37);
	assign f5 = d64;
	and (d64, d2, d65);
	and (d65, d66, d67);
	or (d66, x0, d50);
	and (d67, d12, d68);
	and (d68, d16, d69);
	and (d69, d38, d49);
	assign f6 = d70;
	and (d70, d2, d71);
	and (d71, d66, d72);
	and (d72, d31, d73);
	and (d73, d6, d74);
	and (d74, d12, d75);
	and (d75, d46, d76);
	and (d76, d23, d77);
	and (d77, d27, d78);
	and (d78, d36, d38);
endmodule
