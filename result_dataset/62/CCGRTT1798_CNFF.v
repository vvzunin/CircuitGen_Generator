//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1798_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x3, d9);
	not (d9, x2);
	and (d10, d11, d16);
	or (d11, x0, d12);
	or (d12, d13, d14);
	not (d13, x1);
	or (d14, x2, d15);
	not (d15, x3);
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
	and (d26, d27, d29);
	or (d27, d22, d28);
	or (d28, x1, d19);
	and (d29, d30, d32);
	or (d30, d22, d31);
	or (d31, d4, d13);
	and (d32, d33, d34);
	or (d33, d12, d22);
	or (d34, d22, d35);
	or (d35, d8, d13);
	assign f1 = d36;
	and (d36, d6, d37);
	and (d37, d17, d38);
	and (d38, d21, d39);
	and (d39, d27, d40);
	and (d40, d30, d41);
	or (d41, d18, d22);
	assign f2 = d42;
	and (d42, d43, d44);
	or (d43, x0, d25);
	and (d44, d45, d46);
	or (d45, x0, d28);
	and (d46, d47, d48);
	or (d47, x0, d31);
	and (d48, d11, d49);
	and (d49, d50, d51);
	or (d50, x0, d35);
	and (d51, d21, d52);
	and (d52, d24, d33);
	assign f3 = d53;
	and (d53, d2, d54);
	and (d54, d47, d55);
	and (d55, d11, d56);
	and (d56, d17, d57);
	and (d57, d24, d58);
	and (d58, d27, d59);
	and (d59, d30, d60);
	and (d60, d34, d41);
	assign f4 = d61;
	and (d61, d2, d62);
	and (d62, d43, d63);
	and (d63, d45, d64);
	and (d64, d47, d65);
	and (d65, d11, d66);
	and (d66, d50, d67);
	and (d67, d17, d68);
	and (d68, d21, d69);
	and (d69, d24, d70);
	and (d70, d30, d71);
	and (d71, d33, d60);
endmodule
