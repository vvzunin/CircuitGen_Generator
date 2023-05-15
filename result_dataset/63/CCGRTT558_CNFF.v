//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT558_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82;

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
	or (d17, x1, d18);
	or (d18, d9, d14);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d4, d22);
	not (d22, x1);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d8, d22);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d13, d22);
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, d18, d22);
	and (d32, d33, d35);
	or (d33, d3, d34);
	not (d34, x0);
	and (d35, d36, d37);
	or (d36, d7, d34);
	and (d37, d38, d39);
	or (d38, d12, d34);
	and (d39, d40, d41);
	or (d40, d17, d34);
	or (d41, d31, d34);
	assign f1 = d42;
	and (d42, d6, d43);
	and (d43, d11, d44);
	and (d44, d20, d45);
	and (d45, d24, d46);
	and (d46, d30, d47);
	and (d47, d33, d48);
	and (d48, d38, d49);
	and (d49, d40, d50);
	and (d50, d41, d51);
	or (d51, d28, d34);
	assign f2 = d52;
	and (d52, d6, d53);
	and (d53, d11, d54);
	and (d54, d16, d55);
	and (d55, d33, d56);
	and (d56, d38, d57);
	and (d57, d40, d58);
	and (d58, d59, d60);
	or (d59, d21, d34);
	or (d60, d25, d34);
	assign f3 = d61;
	and (d61, d2, d62);
	and (d62, d6, d63);
	and (d63, d20, d64);
	and (d64, d24, d65);
	and (d65, d30, d66);
	and (d66, d36, d67);
	and (d67, d38, d68);
	and (d68, d59, d69);
	and (d69, d41, d60);
	assign f4 = d70;
	and (d70, d2, d71);
	and (d71, d11, d72);
	and (d72, d16, d73);
	and (d73, d20, d74);
	and (d74, d27, d75);
	and (d75, d30, d76);
	and (d76, d33, d77);
	and (d77, d36, d59);
	assign f5 = d78;
	and (d78, d6, d79);
	and (d79, d11, d80);
	and (d80, d16, d81);
	and (d81, d33, d82);
	and (d82, d50, d59);
endmodule
