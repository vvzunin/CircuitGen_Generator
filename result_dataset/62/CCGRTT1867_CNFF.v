//f0 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3)
//f2 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1867_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d9, d14);
	or (d14, x3, d15);
	not (d15, x2);
	and (d16, d17, d19);
	or (d17, d3, d18);
	not (d18, x0);
	and (d19, d20, d22);
	or (d20, d18, d21);
	or (d21, x1, d14);
	or (d22, d18, d23);
	or (d23, x1, d24);
	or (d24, d5, d15);
	assign f1 = d25;
	and (d25, d26, d28);
	or (d26, x0, d27);
	or (d27, x1, d10);
	and (d28, d29, d30);
	or (d29, x0, d23);
	and (d30, d7, d20);
	assign f2 = d31;
	and (d31, d7, d32);
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, d4, d9);
	and (d35, d20, d36);
	or (d36, d18, d37);
	or (d37, d9, d24);
	assign f3 = d38;
	and (d38, d26, d39);
	and (d39, d2, d40);
	and (d40, d7, d41);
	and (d41, d12, d42);
	or (d42, d18, d34);
	assign f4 = d43;
	and (d43, d2, d44);
	and (d44, d12, d45);
	and (d45, d46, d47);
	or (d46, d18, d27);
	and (d47, d17, d48);
	and (d48, d20, d49);
	and (d49, d22, d50);
	and (d50, d42, d51);
	or (d51, d8, d18);
	assign f5 = d52;
	and (d52, d26, d53);
	and (d53, d29, d54);
	and (d54, d55, d56);
	or (d55, x0, d37);
	and (d56, d17, d57);
	and (d57, d20, d58);
	and (d58, d36, d51);
endmodule
