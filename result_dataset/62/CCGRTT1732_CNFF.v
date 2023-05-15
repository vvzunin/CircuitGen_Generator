//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1732_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65;

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
	and (d15, d16, d18);
	or (d16, d3, d17);
	not (d17, x0);
	and (d18, d19, d22);
	or (d19, d17, d20);
	or (d20, x1, d21);
	or (d21, x3, d14);
	and (d22, d23, d24);
	or (d23, d12, d17);
	or (d24, d17, d25);
	or (d25, d13, d26);
	not (d26, x1);
	assign f1 = d27;
	and (d27, d6, d28);
	and (d28, d16, d29);
	and (d29, d19, d30);
	or (d30, d7, d17);
	assign f2 = d31;
	and (d31, d2, d32);
	and (d32, d11, d33);
	and (d33, d34, d36);
	or (d34, x0, d35);
	or (d35, d4, d26);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d21, d26);
	and (d39, d40, d41);
	or (d40, x0, d25);
	and (d41, d16, d42);
	and (d42, d30, d43);
	and (d43, d23, d44);
	and (d44, d24, d45);
	or (d45, d17, d35);
	assign f3 = d46;
	and (d46, d2, d47);
	and (d47, d11, d48);
	and (d48, d49, d51);
	or (d49, x0, d50);
	or (d50, d8, d26);
	and (d51, d37, d52);
	and (d52, d40, d53);
	and (d53, d23, d54);
	and (d54, d24, d55);
	or (d55, d17, d50);
	assign f4 = d56;
	and (d56, d57, d58);
	or (d57, x0, d20);
	and (d58, d34, d59);
	and (d59, d49, d60);
	and (d60, d37, d61);
	and (d61, d16, d62);
	and (d62, d30, d63);
	and (d63, d19, d64);
	and (d64, d23, d65);
	or (d65, d17, d38);
endmodule
