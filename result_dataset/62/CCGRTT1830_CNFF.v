//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3)
module CCGRTT1830_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

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
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d14, d18);
	and (d22, d23, d27);
	or (d23, d24, d25);
	not (d24, x0);
	or (d25, x1, d26);
	or (d26, x2, x3);
	and (d27, d28, d29);
	or (d28, d8, d24);
	and (d29, d30, d32);
	or (d30, d24, d31);
	or (d31, d18, d26);
	or (d32, d24, d33);
	or (d33, d9, d18);
	assign f1 = d34;
	and (d34, d7, d35);
	and (d35, d36, d37);
	or (d36, x0, d31);
	and (d37, d38, d39);
	or (d38, x0, d33);
	and (d39, d40, d41);
	or (d40, d3, d24);
	or (d41, d21, d24);
	assign f2 = d42;
	and (d42, d43, d44);
	or (d43, x0, d25);
	and (d44, d7, d45);
	and (d45, d12, d46);
	and (d46, d38, d47);
	and (d47, d40, d48);
	and (d48, d49, d50);
	or (d49, d13, d24);
	and (d50, d30, d51);
	and (d51, d32, d41);
	assign f3 = d52;
	and (d52, d43, d53);
	and (d53, d36, d54);
	and (d54, d38, d55);
	and (d55, d20, d56);
	and (d56, d23, d57);
	and (d57, d28, d58);
	and (d58, d49, d59);
	and (d59, d51, d60);
	or (d60, d17, d24);
	assign f4 = d61;
	and (d61, d7, d62);
	and (d62, d38, d63);
	and (d63, d23, d64);
	and (d64, d40, d65);
	and (d65, d28, d41);
	assign f5 = d66;
	and (d66, d43, d67);
	and (d67, d2, d68);
	and (d68, d12, d69);
	and (d69, d36, d70);
	and (d70, d20, d23);
endmodule
