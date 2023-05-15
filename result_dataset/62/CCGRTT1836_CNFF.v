//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1836_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74;

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
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d8, d18);
	and (d22, d23, d25);
	or (d23, x0, d24);
	or (d24, d13, d18);
	and (d25, d26, d28);
	or (d26, d17, d27);
	not (d27, x0);
	or (d28, d21, d27);
	assign f1 = d29;
	and (d29, d11, d30);
	and (d30, d20, d31);
	and (d31, d32, d35);
	or (d32, x0, d33);
	or (d33, d18, d34);
	or (d34, d9, d14);
	and (d35, d36, d37);
	or (d36, d12, d27);
	and (d37, d38, d40);
	or (d38, d27, d39);
	or (d39, x1, d34);
	and (d40, d28, d41);
	and (d41, d42, d43);
	or (d42, d24, d27);
	or (d43, d27, d33);
	assign f2 = d44;
	and (d44, d6, d45);
	and (d45, d46, d47);
	or (d46, x0, d39);
	and (d47, d16, d48);
	and (d48, d20, d49);
	and (d49, d23, d50);
	and (d50, d32, d51);
	and (d51, d52, d53);
	or (d52, d7, d27);
	and (d53, d26, d54);
	and (d54, d28, d43);
	assign f3 = d55;
	and (d55, d2, d56);
	and (d56, d11, d57);
	and (d57, d46, d58);
	and (d58, d16, d59);
	and (d59, d20, d60);
	and (d60, d23, d61);
	and (d61, d62, d63);
	or (d62, d3, d27);
	and (d63, d26, d40);
	assign f4 = d64;
	and (d64, d16, d65);
	and (d65, d20, d66);
	and (d66, d23, d67);
	and (d67, d62, d68);
	and (d68, d36, d69);
	and (d69, d38, d54);
	assign f5 = d70;
	and (d70, d11, d71);
	and (d71, d23, d72);
	and (d72, d32, d73);
	and (d73, d52, d74);
	and (d74, d36, d54);
endmodule
