//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1638_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53;

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
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d8, d13);
	not (d13, x1);
	or (d14, x0, d15);
	or (d15, d13, d16);
	or (d16, x3, d17);
	not (d17, x2);
	assign f1 = d18;
	and (d18, d6, d19);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, x1, d16);
	and (d22, d23, d25);
	or (d23, x0, d24);
	or (d24, d4, d13);
	and (d25, d26, d29);
	or (d26, x0, d27);
	or (d27, d13, d28);
	or (d28, d9, d17);
	and (d29, d30, d32);
	or (d30, d3, d31);
	not (d31, x0);
	and (d32, d33, d35);
	or (d33, d31, d34);
	or (d34, x1, d28);
	and (d35, d36, d37);
	or (d36, d12, d31);
	or (d37, d15, d31);
	assign f2 = d38;
	and (d38, d6, d39);
	and (d39, d20, d40);
	and (d40, d14, d41);
	and (d41, d26, d42);
	and (d42, d43, d44);
	or (d43, d7, d31);
	or (d44, d27, d31);
	assign f3 = d45;
	and (d45, d2, d46);
	and (d46, d11, d47);
	and (d47, d26, d48);
	and (d48, d30, d49);
	and (d49, d43, d50);
	and (d50, d51, d52);
	or (d51, d21, d31);
	and (d52, d36, d53);
	or (d53, d24, d31);
endmodule
