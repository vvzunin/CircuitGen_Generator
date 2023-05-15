//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1778_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x3, d10);
	and (d20, d21, d24);
	or (d21, d22, d23);
	not (d22, x0);
	or (d23, x1, d15);
	and (d24, d25, d26);
	or (d25, d3, d22);
	and (d26, d27, d29);
	or (d27, d22, d28);
	or (d28, x1, d19);
	and (d29, d30, d31);
	or (d30, d13, d22);
	and (d31, d32, d34);
	or (d32, d22, d33);
	or (d33, d4, d14);
	and (d34, d35, d36);
	or (d35, d18, d22);
	or (d36, d22, d37);
	or (d37, d9, d14);
	assign f1 = d38;
	and (d38, d7, d39);
	and (d39, d12, d40);
	and (d40, d17, d41);
	and (d41, d42, d43);
	or (d42, x0, d37);
	and (d43, d25, d44);
	and (d44, d31, d45);
	or (d45, d8, d22);
	assign f2 = d46;
	and (d46, d47, d48);
	or (d47, x0, d23);
	and (d48, d12, d49);
	and (d49, d42, d50);
	and (d50, d27, d51);
	and (d51, d45, d52);
	and (d52, d30, d53);
	and (d53, d32, d36);
	assign f3 = d54;
	and (d54, d47, d55);
	and (d55, d56, d57);
	or (d56, x0, d33);
	and (d57, d17, d58);
	and (d58, d42, d59);
	and (d59, d21, d60);
	and (d60, d45, d61);
	and (d61, d30, d35);
	assign f4 = d62;
	and (d62, d47, d63);
	and (d63, d2, d64);
	and (d64, d7, d65);
	and (d65, d12, d66);
	and (d66, d17, d67);
	and (d67, d30, d68);
	and (d68, d32, d35);
endmodule
