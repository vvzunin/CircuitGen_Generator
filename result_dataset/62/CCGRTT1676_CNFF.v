//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1676_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, x3, d10);
	not (d10, x2);
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, x1, d14);
	or (d14, d5, d10);
	and (d15, d16, d20);
	or (d16, x0, d17);
	or (d17, d18, d19);
	not (d18, x1);
	or (d19, x2, x3);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d14, d18);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d19);
	and (d27, d28, d29);
	or (d28, d3, d25);
	and (d29, d30, d31);
	or (d30, d13, d25);
	or (d31, d17, d25);
	assign f1 = d32;
	and (d32, d2, d33);
	and (d33, d7, d34);
	and (d34, d35, d37);
	or (d35, x0, d36);
	or (d36, d4, d18);
	and (d37, d28, d38);
	and (d38, d39, d40);
	or (d39, d8, d25);
	and (d40, d41, d42);
	or (d41, d25, d36);
	and (d42, d43, d45);
	or (d43, d25, d44);
	or (d44, d9, d18);
	or (d45, d22, d25);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d7, d48);
	and (d48, d12, d49);
	and (d49, d16, d50);
	and (d50, d51, d52);
	or (d51, x0, d44);
	and (d52, d28, d53);
	and (d53, d39, d54);
	and (d54, d31, d55);
	and (d55, d41, d45);
	assign f3 = d56;
	and (d56, d57, d58);
	or (d57, x0, d26);
	and (d58, d12, d59);
	and (d59, d35, d60);
	and (d60, d21, d61);
	and (d61, d24, d37);
endmodule
