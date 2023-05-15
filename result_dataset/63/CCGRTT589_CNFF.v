//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT589_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, d11);
	not (d11, x3);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d9, d15);
	or (d15, d5, d11);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d10);
	and (d20, d21, d24);
	or (d21, d18, d22);
	or (d22, d9, d23);
	or (d23, x2, x3);
	or (d24, d14, d18);
	assign f1 = d25;
	and (d25, d26, d27);
	or (d26, x0, d19);
	and (d27, d13, d28);
	and (d28, d29, d30);
	or (d29, d3, d18);
	or (d30, d18, d31);
	or (d31, d4, d9);
	assign f2 = d32;
	and (d32, d26, d33);
	and (d33, d34, d36);
	or (d34, x0, d35);
	or (d35, x1, d15);
	and (d36, d13, d37);
	and (d37, d21, d38);
	and (d38, d24, d30);
	assign f3 = d27;
	assign f4 = d39;
	and (d39, d40, d42);
	or (d40, x0, d41);
	or (d41, x1, d23);
	and (d42, d26, d43);
	and (d43, d34, d44);
	and (d44, d17, d45);
	and (d45, d29, d46);
	and (d46, d24, d47);
	or (d47, d18, d35);
	assign f5 = d48;
	and (d48, d2, d49);
	and (d49, d34, d50);
	and (d50, d51, d52);
	or (d51, x0, d22);
	and (d52, d53, d54);
	or (d53, x0, d31);
	and (d54, d17, d55);
	and (d55, d29, d37);
	assign f6 = d56;
	and (d56, d34, d57);
	and (d57, d7, d58);
	and (d58, d59, d60);
	or (d59, d18, d41);
	and (d60, d21, d61);
	and (d61, d30, d62);
	or (d62, d8, d18);
endmodule
