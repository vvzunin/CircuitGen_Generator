//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1804_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, d9, d10);
	not (d9, x2);
	not (d10, x3);
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d20);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d19);
	or (d19, x3, d9);
	and (d20, d21, d22);
	or (d21, d13, d17);
	and (d22, d23, d26);
	or (d23, d17, d24);
	or (d24, d14, d25);
	or (d25, x2, d10);
	or (d26, d17, d27);
	or (d27, d8, d14);
	assign f1 = d28;
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, x1, d25);
	and (d31, d32, d33);
	or (d32, x0, d18);
	and (d33, d6, d34);
	and (d34, d35, d37);
	or (d35, x0, d36);
	or (d36, d14, d19);
	and (d37, d38, d39);
	or (d38, d17, d30);
	and (d39, d21, d40);
	or (d40, d7, d17);
	assign f2 = d41;
	and (d41, d29, d42);
	and (d42, d6, d43);
	and (d43, d44, d45);
	or (d44, x0, d24);
	and (d45, d35, d46);
	and (d46, d47, d48);
	or (d47, d3, d17);
	and (d48, d16, d23);
	assign f3 = d49;
	and (d49, d29, d50);
	and (d50, d32, d51);
	and (d51, d6, d52);
	and (d52, d53, d54);
	or (d53, x0, d27);
	and (d54, d47, d55);
	and (d55, d16, d56);
	and (d56, d40, d57);
	and (d57, d26, d58);
	or (d58, d17, d36);
	assign f4 = d59;
	and (d59, d32, d60);
	and (d60, d35, d61);
	and (d61, d53, d62);
	and (d62, d15, d38);
	assign f5 = d63;
	and (d63, d2, d64);
	and (d64, d32, d65);
	and (d65, d6, d66);
	and (d66, d35, d67);
	and (d67, d22, d53);
endmodule
