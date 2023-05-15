//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1907_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, d6);
	not (d5, x2);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d10, d11);
	not (d10, x1);
	or (d11, x2, d6);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d10, d15);
	or (d15, d5, x3);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d10);
	and (d19, d20, d24);
	or (d20, d21, d22);
	not (d21, x0);
	or (d22, x1, d23);
	or (d23, x2, x3);
	and (d24, d25, d27);
	or (d25, d21, d26);
	or (d26, x1, d11);
	and (d27, d28, d29);
	or (d28, d3, d21);
	and (d29, d30, d31);
	or (d30, d9, d21);
	or (d31, d18, d21);
	assign f1 = d32;
	and (d32, d33, d34);
	or (d33, x0, d22);
	and (d34, d35, d36);
	or (d35, x0, d26);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d10, d23);
	and (d39, d8, d40);
	and (d40, d13, d41);
	and (d41, d42, d43);
	or (d42, d21, d38);
	and (d43, d30, d44);
	or (d44, d14, d21);
	assign f2 = d45;
	and (d45, d35, d46);
	and (d46, d2, d47);
	and (d47, d37, d48);
	and (d48, d42, d49);
	or (d49, d21, d50);
	or (d50, x1, d15);
	assign f3 = d51;
	and (d51, d33, d52);
	and (d52, d17, d53);
	and (d53, d20, d54);
	and (d54, d49, d55);
	and (d55, d28, d56);
	and (d56, d31, d44);
	assign f4 = d57;
	and (d57, d58, d59);
	or (d58, x0, d50);
	and (d59, d2, d60);
	and (d60, d13, d61);
	and (d61, d25, d56);
	assign f5 = d62;
	and (d62, d33, d63);
	and (d63, d2, d64);
	and (d64, d17, d65);
	and (d65, d28, d44);
	assign f6 = d66;
	and (d66, d33, d67);
	and (d67, d35, d68);
	and (d68, d2, d69);
	and (d69, d37, d70);
	and (d70, d8, d71);
	and (d71, d13, d72);
	and (d72, d20, d73);
	and (d73, d25, d74);
	and (d74, d44, d49);
endmodule
