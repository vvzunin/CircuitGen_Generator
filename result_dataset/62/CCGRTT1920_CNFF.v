//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1920_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, d11);
	not (d11, x3);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d9, d15);
	or (d15, d5, d11);
	and (d16, d17, d19);
	or (d17, d3, d18);
	not (d18, x0);
	and (d19, d20, d22);
	or (d20, d18, d21);
	or (d21, x1, d15);
	and (d22, d23, d26);
	or (d23, d18, d24);
	or (d24, d9, d25);
	or (d25, x2, x3);
	and (d26, d27, d29);
	or (d27, d18, d28);
	or (d28, d4, d9);
	or (d29, d14, d18);
	assign f1 = d30;
	and (d30, d2, d31);
	and (d31, d7, d32);
	and (d32, d33, d34);
	or (d33, x0, d28);
	and (d34, d35, d37);
	or (d35, d18, d36);
	or (d36, x1, d25);
	and (d37, d17, d38);
	and (d38, d20, d39);
	and (d39, d23, d40);
	and (d40, d27, d41);
	or (d41, d8, d18);
	assign f2 = d42;
	and (d42, d2, d43);
	and (d43, d7, d44);
	and (d44, d13, d45);
	and (d45, d35, d46);
	and (d46, d39, d47);
	or (d47, d18, d48);
	or (d48, x1, d10);
	assign f3 = d49;
	and (d49, d50, d51);
	or (d50, x0, d21);
	and (d51, d33, d52);
	and (d52, d35, d53);
	and (d53, d47, d54);
	and (d54, d17, d55);
	and (d55, d20, d29);
	assign f4 = d56;
	and (d56, d57, d58);
	or (d57, x0, d36);
	and (d58, d59, d60);
	or (d59, x0, d48);
	and (d60, d2, d61);
	and (d61, d62, d63);
	or (d62, x0, d24);
	and (d63, d7, d64);
	and (d64, d33, d65);
	and (d65, d35, d66);
	and (d66, d17, d67);
	and (d67, d20, d41);
	assign f5 = d68;
	and (d68, d57, d69);
	and (d69, d13, d70);
	and (d70, d35, d71);
	and (d71, d47, d72);
	and (d72, d20, d73);
	and (d73, d23, d74);
	and (d74, d26, d41);
	assign f6 = d75;
	and (d75, d57, d76);
	and (d76, d59, d77);
	and (d77, d2, d78);
	and (d78, d7, d79);
	and (d79, d13, d80);
	and (d80, d47, d81);
	and (d81, d17, d82);
	and (d82, d20, d74);
endmodule
