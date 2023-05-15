//f0 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3)
module CCGRTT1902_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, d6);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d4, d10);
	or (d10, x3, d11);
	not (d11, x2);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d4, d15);
	or (d15, d6, d11);
	and (d16, d17, d21);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d20);
	or (d20, x2, x3);
	and (d21, d22, d24);
	or (d22, d18, d23);
	or (d23, x1, d5);
	or (d24, d18, d25);
	or (d25, d4, d20);
	assign f1 = d26;
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, x1, d10);
	and (d29, d8, d30);
	and (d30, d17, d22);
	assign f2 = d31;
	and (d31, d32, d33);
	or (d32, x0, d23);
	and (d33, d27, d34);
	and (d34, d35, d37);
	or (d35, x0, d36);
	or (d36, x1, d15);
	and (d37, d38, d39);
	or (d38, x0, d25);
	and (d39, d8, d40);
	and (d40, d17, d41);
	and (d41, d42, d43);
	or (d42, d18, d28);
	or (d43, d14, d18);
	assign f3 = d44;
	and (d44, d45, d46);
	or (d45, x0, d19);
	and (d46, d32, d47);
	and (d47, d35, d48);
	and (d48, d13, d49);
	and (d49, d24, d50);
	and (d50, d43, d51);
	or (d51, d3, d18);
	assign f4 = d52;
	and (d52, d2, d53);
	and (d53, d13, d54);
	and (d54, d17, d55);
	and (d55, d56, d57);
	or (d56, d18, d36);
	and (d57, d51, d58);
	and (d58, d43, d59);
	or (d59, d9, d18);
	assign f5 = d60;
	and (d60, d45, d61);
	and (d61, d32, d62);
	and (d62, d27, d63);
	and (d63, d56, d64);
	and (d64, d24, d51);
	assign f6 = d65;
	and (d65, d45, d66);
	and (d66, d27, d67);
	and (d67, d38, d68);
	and (d68, d2, d69);
	and (d69, d8, d17);
endmodule
