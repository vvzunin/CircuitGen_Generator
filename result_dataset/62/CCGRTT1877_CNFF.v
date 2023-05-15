//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1877_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, d8, d9);
	not (d8, x1);
	or (d9, x2, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d8, d14);
	or (d14, x3, d15);
	not (d15, x2);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d8, d19);
	or (d19, d10, d15);
	and (d20, d21, d23);
	or (d21, d3, d22);
	not (d22, x0);
	and (d23, d24, d26);
	or (d24, d22, d25);
	or (d25, x1, d9);
	and (d26, d27, d29);
	or (d27, d22, d28);
	or (d28, x1, d19);
	and (d29, d30, d31);
	or (d30, d7, d22);
	or (d31, d18, d22);
	assign f1 = d32;
	and (d32, d12, d33);
	and (d33, d21, d34);
	and (d34, d24, d35);
	and (d35, d29, d36);
	or (d36, d22, d37);
	or (d37, x1, d14);
	assign f2 = d38;
	and (d38, d2, d39);
	and (d39, d40, d41);
	or (d40, x0, d37);
	and (d41, d42, d43);
	or (d42, x0, d28);
	and (d43, d44, d46);
	or (d44, x0, d45);
	or (d45, d4, d8);
	and (d46, d21, d47);
	and (d47, d24, d48);
	and (d48, d36, d49);
	and (d49, d27, d50);
	or (d50, d13, d22);
	assign f3 = d51;
	and (d51, d52, d53);
	or (d52, x0, d25);
	and (d53, d40, d54);
	and (d54, d42, d55);
	and (d55, d17, d56);
	and (d56, d21, d57);
	and (d57, d27, d58);
	and (d58, d31, d50);
	assign f4 = d59;
	and (d59, d52, d60);
	and (d60, d6, d61);
	and (d61, d17, d62);
	and (d62, d36, d63);
	and (d63, d27, d64);
	and (d64, d31, d65);
	or (d65, d22, d45);
	assign f5 = d66;
	and (d66, d40, d67);
	and (d67, d42, d68);
	and (d68, d6, d69);
	and (d69, d12, d70);
	and (d70, d17, d71);
	and (d71, d36, d72);
	and (d72, d27, d73);
	and (d73, d30, d65);
endmodule
