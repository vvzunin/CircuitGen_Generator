//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1664_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x2, d9);
	not (d9, x3);
	and (d10, d11, d16);
	or (d11, x0, d12);
	or (d12, d13, d14);
	not (d13, x1);
	or (d14, x3, d15);
	not (d15, x2);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d13, d19);
	or (d19, d9, d15);
	and (d20, d21, d23);
	or (d21, d3, d22);
	not (d22, x0);
	and (d23, d24, d25);
	or (d24, d7, d22);
	and (d25, d26, d28);
	or (d26, d22, d27);
	or (d27, x1, d14);
	and (d28, d29, d31);
	or (d29, d22, d30);
	or (d30, x1, d19);
	and (d31, d32, d34);
	or (d32, d22, d33);
	or (d33, d4, d13);
	and (d34, d35, d36);
	or (d35, d12, d22);
	or (d36, d18, d22);
	assign f1 = d37;
	and (d37, d6, d38);
	and (d38, d39, d40);
	or (d39, x0, d27);
	and (d40, d41, d42);
	or (d41, x0, d33);
	and (d42, d43, d45);
	or (d43, x0, d44);
	or (d44, d8, d13);
	and (d45, d11, d46);
	and (d46, d21, d47);
	and (d47, d29, d48);
	and (d48, d32, d49);
	and (d49, d36, d50);
	or (d50, d22, d44);
	assign f2 = d51;
	and (d51, d6, d52);
	and (d52, d41, d53);
	and (d53, d43, d54);
	and (d54, d11, d55);
	and (d55, d17, d56);
	and (d56, d21, d57);
	and (d57, d24, d58);
	and (d58, d29, d59);
	and (d59, d32, d60);
	and (d60, d35, d50);
	assign f3 = d61;
	and (d61, d6, d62);
	and (d62, d39, d63);
	and (d63, d43, d64);
	and (d64, d11, d65);
	and (d65, d21, d49);
endmodule
