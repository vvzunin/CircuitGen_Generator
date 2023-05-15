//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1705_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64;

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
	or (d14, d10, d15);
	not (d15, x2);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d9);
	and (d20, d21, d23);
	or (d21, d18, d22);
	or (d22, d4, d8);
	and (d23, d24, d25);
	or (d24, d7, d18);
	or (d25, d18, d26);
	or (d26, d8, d27);
	or (d27, x3, d15);
	assign f1 = d28;
	and (d28, d2, d29);
	and (d29, d30, d31);
	or (d30, x0, d19);
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, x1, d27);
	and (d34, d35, d36);
	or (d35, x0, d26);
	and (d36, d17, d37);
	and (d37, d21, d38);
	or (d38, d18, d39);
	or (d39, x1, d14);
	assign f2 = d40;
	and (d40, d2, d41);
	and (d41, d32, d42);
	and (d42, d43, d44);
	or (d43, x0, d39);
	and (d44, d45, d46);
	or (d45, x0, d22);
	and (d46, d12, d47);
	and (d47, d17, d48);
	and (d48, d49, d50);
	or (d49, d18, d33);
	and (d50, d24, d51);
	and (d51, d25, d52);
	or (d52, d13, d18);
	assign f3 = d53;
	and (d53, d45, d54);
	and (d54, d35, d55);
	and (d55, d12, d56);
	and (d56, d57, d58);
	or (d57, d3, d18);
	and (d58, d23, d38);
	assign f4 = d59;
	and (d59, d2, d60);
	and (d60, d6, d61);
	and (d61, d17, d62);
	and (d62, d49, d63);
	and (d63, d38, d64);
	and (d64, d24, d52);
endmodule
