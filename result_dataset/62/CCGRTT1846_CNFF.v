//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1846_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73;

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
	and (d10, d11, d16);
	or (d11, x0, d12);
	or (d12, d13, d14);
	not (d13, x1);
	or (d14, x3, d15);
	not (d15, x2);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d13, d19);
	or (d19, d9, d15);
	and (d20, d21, d23);
	or (d21, d3, d22);
	not (d22, x0);
	and (d23, d24, d26);
	or (d24, d22, d25);
	or (d25, x1, d14);
	or (d26, d22, d27);
	or (d27, x1, d19);
	assign f1 = d28;
	and (d28, d29, d30);
	or (d29, x0, d25);
	and (d30, d31, d32);
	or (d31, x0, d27);
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, d4, d13);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d8, d13);
	and (d38, d17, d39);
	and (d39, d21, d40);
	and (d40, d41, d42);
	or (d41, d7, d22);
	and (d42, d26, d43);
	and (d43, d44, d45);
	or (d44, d22, d34);
	and (d45, d46, d47);
	or (d46, d12, d22);
	or (d47, d18, d22);
	assign f2 = d48;
	and (d48, d2, d49);
	and (d49, d6, d50);
	and (d50, d29, d51);
	and (d51, d31, d52);
	and (d52, d36, d53);
	and (d53, d17, d54);
	and (d54, d24, d55);
	and (d55, d26, d45);
	assign f3 = d56;
	and (d56, d2, d57);
	and (d57, d31, d58);
	and (d58, d33, d59);
	and (d59, d36, d60);
	and (d60, d11, d46);
	assign f4 = d61;
	and (d61, d2, d62);
	and (d62, d36, d63);
	and (d63, d21, d64);
	and (d64, d41, d65);
	and (d65, d24, d66);
	and (d66, d47, d67);
	or (d67, d22, d37);
	assign f5 = d68;
	and (d68, d2, d69);
	and (d69, d6, d70);
	and (d70, d29, d71);
	and (d71, d11, d72);
	and (d72, d41, d73);
	and (d73, d44, d67);
endmodule
