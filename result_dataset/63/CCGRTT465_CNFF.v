//f0 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT465_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d4, d9);
	or (d9, x2, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d4, d14);
	or (d14, x3, d15);
	not (d15, x2);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d5);
	and (d20, d21, d24);
	or (d21, d18, d22);
	or (d22, x1, d23);
	or (d23, d10, d15);
	or (d24, d18, d25);
	or (d25, d4, d23);
	assign f1 = d26;
	and (d26, d27, d28);
	or (d27, x0, d19);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, x1, d9);
	and (d31, d32, d33);
	or (d32, x0, d22);
	and (d33, d7, d34);
	and (d34, d35, d36);
	or (d35, x0, d25);
	and (d36, d37, d38);
	or (d37, d18, d30);
	and (d38, d39, d41);
	or (d39, d18, d40);
	or (d40, x1, d14);
	and (d41, d42, d43);
	or (d42, d3, d18);
	and (d43, d24, d44);
	or (d44, d8, d18);
	assign f2 = d45;
	and (d45, d27, d46);
	and (d46, d47, d48);
	or (d47, x0, d40);
	and (d48, d2, d49);
	and (d49, d17, d50);
	and (d50, d37, d51);
	and (d51, d39, d52);
	and (d52, d21, d53);
	and (d53, d44, d54);
	or (d54, d13, d18);
endmodule
