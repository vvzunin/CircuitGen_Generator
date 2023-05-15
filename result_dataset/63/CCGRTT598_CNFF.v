//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT598_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, x1, d14);
	or (d14, d5, d10);
	and (d15, d16, d20);
	or (d16, x0, d17);
	or (d17, d18, d19);
	not (d18, x1);
	or (d19, x2, x3);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d4, d18);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d19);
	and (d27, d28, d29);
	or (d28, d8, d25);
	or (d29, d13, d25);
	assign f1 = d30;
	and (d30, d31, d32);
	or (d31, x0, d26);
	and (d32, d7, d33);
	and (d33, d12, d34);
	and (d34, d16, d35);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d9, d18);
	and (d38, d39, d41);
	or (d39, x0, d40);
	or (d40, d14, d18);
	and (d41, d24, d42);
	and (d42, d43, d44);
	or (d43, d3, d25);
	and (d44, d45, d46);
	or (d45, d22, d25);
	and (d46, d47, d48);
	or (d47, d25, d37);
	or (d48, d25, d40);
	assign f2 = d49;
	and (d49, d2, d50);
	and (d50, d7, d51);
	and (d51, d12, d52);
	and (d52, d16, d53);
	and (d53, d36, d54);
	and (d54, d39, d55);
	and (d55, d29, d48);
	assign f3 = d56;
	and (d56, d2, d57);
	and (d57, d7, d58);
	and (d58, d21, d59);
	and (d59, d36, d60);
	and (d60, d39, d61);
	and (d61, d29, d62);
	and (d62, d45, d48);
	assign f4 = d63;
	and (d63, d2, d64);
	and (d64, d7, d65);
	and (d65, d24, d66);
	and (d66, d43, d67);
	and (d67, d29, d47);
	assign f5 = d68;
	and (d68, d2, d69);
	and (d69, d12, d70);
	and (d70, d36, d71);
	and (d71, d39, d65);
	assign f6 = d72;
	and (d72, d31, d73);
	and (d73, d16, d74);
	and (d74, d21, d75);
	and (d75, d39, d76);
	and (d76, d24, d77);
	and (d77, d43, d78);
	and (d78, d46, d79);
	or (d79, d17, d25);
endmodule
