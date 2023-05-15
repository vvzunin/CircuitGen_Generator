//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1649_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, d6);
	not (d5, x2);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d10, d11);
	not (d10, x1);
	or (d11, x2, d6);
	and (d12, d13, d15);
	or (d13, d3, d14);
	not (d14, x0);
	and (d15, d16, d19);
	or (d16, d14, d17);
	or (d17, d10, d18);
	or (d18, x2, x3);
	and (d19, d20, d23);
	or (d20, d14, d21);
	or (d21, d10, d22);
	or (d22, d5, x3);
	or (d23, d14, d24);
	or (d24, d4, d10);
	assign f1 = d25;
	and (d25, d26, d28);
	or (d26, x0, d27);
	or (d27, x1, d18);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, x1, d11);
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, x1, d22);
	and (d34, d35, d36);
	or (d35, x0, d21);
	and (d36, d37, d38);
	or (d37, d14, d33);
	and (d38, d20, d39);
	or (d39, d9, d14);
	assign f2 = d40;
	and (d40, d29, d41);
	and (d41, d2, d42);
	and (d42, d8, d43);
	and (d43, d44, d45);
	or (d44, x0, d24);
	and (d45, d46, d47);
	or (d46, d14, d30);
	and (d47, d16, d38);
	assign f3 = d48;
	and (d48, d32, d49);
	and (d49, d8, d50);
	and (d50, d44, d51);
	and (d51, d46, d52);
	and (d52, d16, d53);
	and (d53, d19, d39);
endmodule
