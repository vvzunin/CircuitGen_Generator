//f0 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1838_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d10);
	or (d7, x0, d8);
	or (d8, d4, d9);
	not (d9, x1);
	and (d10, d11, d16);
	or (d11, d12, d13);
	not (d12, x0);
	or (d13, x1, d14);
	or (d14, d5, d15);
	not (d15, x2);
	or (d16, d8, d12);
	assign f1 = d17;
	and (d17, d18, d21);
	or (d18, x0, d19);
	or (d19, x1, d20);
	or (d20, x2, x3);
	and (d21, d2, d22);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, x1, d25);
	or (d25, x3, d15);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d9, d20);
	and (d29, d7, d30);
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, d9, d14);
	and (d33, d11, d34);
	and (d34, d16, d35);
	or (d35, d12, d36);
	or (d36, d9, d25);
	assign f2 = d37;
	and (d37, d23, d38);
	and (d38, d7, d39);
	and (d39, d40, d41);
	or (d40, x0, d36);
	and (d41, d31, d42);
	and (d42, d43, d44);
	or (d43, d3, d12);
	and (d44, d11, d45);
	and (d45, d16, d46);
	or (d46, d12, d28);
	assign f3 = d47;
	and (d47, d18, d48);
	and (d48, d31, d49);
	and (d49, d50, d51);
	or (d50, d12, d19);
	and (d51, d43, d52);
	and (d52, d11, d53);
	and (d53, d46, d54);
	or (d54, d12, d32);
	assign f4 = d55;
	and (d55, d7, d56);
	and (d56, d31, d57);
	and (d57, d43, d58);
	or (d58, d12, d24);
	assign f5 = d59;
	and (d59, d2, d30);
endmodule
