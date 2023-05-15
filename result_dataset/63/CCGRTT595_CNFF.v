//f0 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT595_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, x3);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d4, d9);
	or (d9, d10, d11);
	not (d10, x2);
	not (d11, x3);
	and (d12, d13, d16);
	or (d13, d14, d15);
	not (d14, x0);
	or (d15, x1, d5);
	and (d16, d17, d20);
	or (d17, d14, d18);
	or (d18, x1, d19);
	or (d19, x2, d11);
	and (d20, d21, d24);
	or (d21, d14, d22);
	or (d22, x1, d23);
	or (d23, x3, d10);
	and (d24, d25, d27);
	or (d25, d14, d26);
	or (d26, x1, d9);
	and (d27, d28, d30);
	or (d28, d14, d29);
	or (d29, d4, d19);
	or (d30, d8, d14);
	assign f1 = d31;
	and (d31, d32, d33);
	or (d32, x0, d15);
	and (d33, d34, d35);
	or (d34, x0, d18);
	and (d35, d36, d37);
	or (d36, x0, d22);
	and (d37, d2, d38);
	and (d38, d39, d41);
	or (d39, x0, d40);
	or (d40, d4, d23);
	and (d41, d7, d42);
	and (d42, d13, d43);
	and (d43, d17, d28);
	assign f2 = d44;
	and (d44, d7, d25);
	assign f3 = d45;
	and (d45, d32, d46);
	and (d46, d34, d47);
	and (d47, d36, d48);
	and (d48, d49, d50);
	or (d49, x0, d26);
	and (d50, d51, d52);
	or (d51, x0, d29);
	and (d52, d7, d53);
	and (d53, d13, d54);
	and (d54, d21, d30);
	assign f4 = d55;
	and (d55, d32, d56);
	and (d56, d34, d57);
	and (d57, d36, d58);
	and (d58, d2, d59);
	and (d59, d51, d60);
	and (d60, d13, d61);
	and (d61, d21, d62);
	and (d62, d25, d28);
	assign f5 = d63;
	and (d63, d32, d64);
	and (d64, d34, d65);
	and (d65, d36, d66);
	and (d66, d49, d67);
	and (d67, d2, d68);
	and (d68, d39, d69);
	and (d69, d13, d27);
	assign f6 = d70;
	and (d70, d32, d71);
	and (d71, d34, d72);
	and (d72, d36, d73);
	and (d73, d2, d74);
	and (d74, d39, d75);
	and (d75, d13, d76);
	and (d76, d21, d77);
	and (d77, d25, d78);
	and (d78, d27, d79);
	or (d79, d3, d14);
endmodule
