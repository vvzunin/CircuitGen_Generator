//f0 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT1861_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x3, d11);
	not (d11, x2);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d9, d15);
	or (d15, d5, d11);
	and (d16, d17, d21);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d20);
	or (d20, x2, x3);
	and (d21, d22, d23);
	or (d22, d3, d18);
	and (d23, d24, d26);
	or (d24, d18, d25);
	or (d25, d9, d20);
	and (d26, d27, d29);
	or (d27, d18, d28);
	or (d28, d4, d9);
	and (d29, d30, d31);
	or (d30, d8, d18);
	or (d31, d14, d18);
	assign f1 = d32;
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, x1, d10);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, x1, d15);
	and (d38, d39, d40);
	or (d39, x0, d28);
	and (d40, d7, d41);
	and (d41, d13, d42);
	and (d42, d22, d43);
	and (d43, d44, d45);
	or (d44, d18, d34);
	and (d45, d23, d46);
	or (d46, d18, d37);
	assign f2 = d47;
	and (d47, d48, d49);
	or (d48, x0, d19);
	and (d49, d2, d50);
	and (d50, d51, d52);
	or (d51, x0, d25);
	and (d52, d13, d53);
	and (d53, d17, d54);
	and (d54, d44, d55);
	and (d55, d27, d30);
	assign f3 = d56;
	and (d56, d2, d57);
	and (d57, d36, d54);
	assign f4 = d58;
	and (d58, d33, d59);
	and (d59, d39, d60);
	and (d60, d13, d61);
	and (d61, d44, d62);
	and (d62, d27, d46);
	assign f5 = d63;
	and (d63, d51, d64);
	and (d64, d39, d65);
	and (d65, d17, d66);
	and (d66, d44, d67);
	and (d67, d24, d46);
endmodule
