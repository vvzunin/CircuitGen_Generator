//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT1853_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

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
	or (d13, d9, d14);
	not (d14, x1);
	and (d15, d16, d18);
	or (d16, d3, d17);
	not (d17, x0);
	and (d18, d19, d22);
	or (d19, d17, d20);
	or (d20, x1, d21);
	or (d21, d5, d10);
	and (d22, d23, d25);
	or (d23, d17, d24);
	or (d24, d4, d14);
	or (d25, d13, d17);
	assign f1 = d26;
	and (d26, d7, d27);
	and (d27, d28, d29);
	or (d28, x0, d20);
	and (d29, d30, d33);
	or (d30, x0, d31);
	or (d31, d14, d32);
	or (d32, x2, x3);
	and (d33, d34, d35);
	or (d34, x0, d24);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d14, d21);
	and (d38, d39, d41);
	or (d39, d17, d40);
	or (d40, x1, d32);
	and (d41, d16, d42);
	and (d42, d19, d43);
	and (d43, d23, d44);
	or (d44, d17, d31);
	assign f2 = d45;
	and (d45, d30, d46);
	and (d46, d34, d47);
	and (d47, d16, d48);
	and (d48, d44, d49);
	and (d49, d23, d50);
	or (d50, d17, d37);
	assign f3 = d51;
	and (d51, d52, d53);
	or (d52, x0, d40);
	and (d53, d2, d54);
	and (d54, d30, d55);
	and (d55, d12, d56);
	and (d56, d36, d57);
	and (d57, d39, d58);
	and (d58, d59, d60);
	or (d59, d8, d17);
	and (d60, d44, d61);
	and (d61, d23, d62);
	and (d62, d25, d50);
	assign f4 = d63;
	and (d63, d52, d64);
	and (d64, d2, d65);
	and (d65, d7, d66);
	and (d66, d28, d67);
	and (d67, d30, d68);
	and (d68, d34, d69);
	and (d69, d50, d59);
	assign f5 = d70;
	and (d70, d2, d71);
	and (d71, d30, d72);
	and (d72, d39, d44);
endmodule
