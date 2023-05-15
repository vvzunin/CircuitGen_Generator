//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1863_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d9, d14);
	not (d14, x1);
	and (d15, d16, d20);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d19);
	or (d19, x2, x3);
	and (d20, d21, d24);
	or (d21, d17, d22);
	or (d22, x1, d23);
	or (d23, x3, d10);
	and (d24, d25, d27);
	or (d25, d17, d26);
	or (d26, d14, d19);
	and (d27, d28, d30);
	or (d28, d17, d29);
	or (d29, d14, d23);
	or (d30, d13, d17);
	assign f1 = d31;
	and (d31, d2, d32);
	and (d32, d33, d34);
	or (d33, x0, d22);
	and (d34, d7, d35);
	and (d35, d36, d37);
	or (d36, x0, d29);
	and (d37, d16, d25);
	assign f2 = d38;
	and (d38, d39, d40);
	or (d39, x0, d18);
	and (d40, d2, d41);
	and (d41, d7, d42);
	and (d42, d43, d44);
	or (d43, x0, d26);
	and (d44, d16, d45);
	and (d45, d46, d47);
	or (d46, d3, d17);
	and (d47, d25, d48);
	and (d48, d27, d49);
	or (d49, d17, d50);
	or (d50, d4, d14);
	assign f3 = d51;
	and (d51, d2, d52);
	and (d52, d33, d53);
	and (d53, d7, d54);
	and (d54, d16, d55);
	and (d55, d25, d56);
	and (d56, d30, d49);
	assign f4 = d57;
	and (d57, d39, d58);
	and (d58, d2, d59);
	and (d59, d7, d60);
	and (d60, d43, d61);
	and (d61, d36, d62);
	and (d62, d16, d63);
	and (d63, d21, d55);
	assign f5 = d64;
	and (d64, d39, d65);
	and (d65, d2, d66);
	and (d66, d7, d67);
	and (d67, d46, d68);
	and (d68, d25, d49);
endmodule
