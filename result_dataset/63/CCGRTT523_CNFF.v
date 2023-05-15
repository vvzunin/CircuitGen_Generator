//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT523_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	and (d11, d12, d14);
	or (d12, d3, d13);
	not (d13, x0);
	and (d14, d15, d16);
	or (d15, d8, d13);
	or (d16, d13, d17);
	or (d17, d18, d19);
	not (d18, x1);
	or (d19, x2, x3);
	assign f1 = d20;
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, x1, d19);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d4, d18);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d9, d18);
	and (d29, d30, d31);
	or (d30, d13, d22);
	and (d31, d12, d32);
	and (d32, d15, d33);
	or (d33, d13, d34);
	or (d34, d18, d35);
	or (d35, x3, d10);
	assign f2 = d36;
	and (d36, d2, d37);
	and (d37, d38, d40);
	or (d38, x0, d39);
	or (d39, x1, d35);
	and (d40, d41, d42);
	or (d41, x0, d17);
	and (d42, d24, d43);
	and (d43, d30, d44);
	and (d44, d12, d45);
	and (d45, d46, d47);
	or (d46, d13, d39);
	and (d47, d33, d48);
	or (d48, d13, d25);
	assign f3 = d49;
	and (d49, d7, d50);
	and (d50, d24, d51);
	and (d51, d52, d53);
	or (d52, x0, d34);
	and (d53, d30, d54);
	and (d54, d12, d55);
	and (d55, d46, d56);
	and (d56, d48, d57);
	and (d57, d33, d58);
	or (d58, d13, d28);
	assign f4 = d59;
	and (d59, d21, d60);
	and (d60, d38, d61);
	and (d61, d7, d62);
	and (d62, d41, d63);
	and (d63, d52, d64);
	and (d64, d46, d65);
	and (d65, d16, d48);
endmodule
