//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1545_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, d9, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d8, d18);
	and (d22, d23, d27);
	or (d23, d24, d25);
	not (d24, x0);
	or (d25, x1, d26);
	or (d26, x3, d14);
	or (d27, d21, d24);
	assign f1 = d28;
	and (d28, d2, d29);
	and (d29, d11, d30);
	and (d30, d16, d31);
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, d18, d26);
	and (d34, d35, d36);
	or (d35, d7, d24);
	and (d36, d27, d37);
	or (d37, d12, d24);
	assign f2 = d38;
	and (d38, d6, d39);
	and (d39, d11, d40);
	and (d40, d20, d41);
	and (d41, d32, d42);
	and (d42, d43, d44);
	or (d43, d3, d24);
	and (d44, d37, d45);
	and (d45, d46, d47);
	or (d46, d17, d24);
	or (d47, d24, d48);
	or (d48, d13, d18);
endmodule
