//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1726_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62;

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
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d9, d14);
	and (d19, d20, d22);
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d26);
	or (d23, d21, d24);
	or (d24, x1, d25);
	or (d25, x3, d10);
	or (d26, d18, d21);
	assign f1 = d27;
	and (d27, d28, d30);
	or (d28, x0, d29);
	or (d29, x1, d15);
	and (d30, d2, d31);
	and (d31, d32, d33);
	or (d32, x0, d24);
	and (d33, d7, d34);
	and (d34, d35, d37);
	or (d35, x0, d36);
	or (d36, d4, d14);
	and (d37, d38, d40);
	or (d38, x0, d39);
	or (d39, d14, d25);
	and (d40, d20, d41);
	and (d41, d42, d43);
	or (d42, d13, d21);
	and (d43, d44, d45);
	or (d44, d21, d36);
	or (d45, d21, d39);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d32, d48);
	and (d48, d12, d49);
	and (d49, d35, d50);
	and (d50, d38, d51);
	and (d51, d17, d52);
	and (d52, d53, d54);
	or (d53, d21, d29);
	and (d54, d20, d55);
	and (d55, d42, d56);
	and (d56, d26, d45);
	assign f3 = d57;
	and (d57, d2, d58);
	and (d58, d17, d59);
	and (d59, d53, d60);
	and (d60, d20, d26);
	assign f4 = d61;
	and (d61, d28, d62);
	and (d62, d35, d44);
endmodule
