//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1711_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58;

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
	or (d11, x2, x3);
	and (d12, d13, d16);
	or (d13, d14, d15);
	not (d14, x0);
	or (d15, x1, d11);
	or (d16, d14, d17);
	or (d17, d4, d10);
	assign f1 = d18;
	and (d18, d19, d22);
	or (d19, x0, d20);
	or (d20, x1, d21);
	or (d21, x2, d6);
	and (d22, d23, d25);
	or (d23, x0, d24);
	or (d24, d10, d21);
	and (d25, d13, d26);
	and (d26, d27, d28);
	or (d27, d9, d14);
	and (d28, d29, d30);
	or (d29, d14, d24);
	or (d30, d14, d31);
	or (d31, d10, d32);
	or (d32, d5, x3);
	assign f2 = d33;
	and (d33, d34, d35);
	or (d34, x0, d15);
	and (d35, d8, d36);
	and (d36, d37, d38);
	or (d37, d14, d20);
	and (d38, d39, d41);
	or (d39, d14, d40);
	or (d40, x1, d32);
	and (d41, d42, d43);
	or (d42, d3, d14);
	and (d43, d27, d44);
	and (d44, d16, d29);
	assign f3 = d45;
	and (d45, d2, d46);
	and (d46, d8, d47);
	and (d47, d23, d48);
	and (d48, d49, d50);
	or (d49, x0, d17);
	and (d50, d27, d30);
	assign f4 = d51;
	and (d51, d34, d52);
	and (d52, d8, d53);
	and (d53, d23, d54);
	and (d54, d55, d56);
	or (d55, x0, d31);
	and (d56, d49, d57);
	and (d57, d13, d58);
	and (d58, d16, d39);
endmodule
