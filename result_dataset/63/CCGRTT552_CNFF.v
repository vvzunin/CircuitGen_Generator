//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT552_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

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
	or (d22, d4, d18);
	and (d23, d24, d26);
	or (d24, d13, d25);
	not (d25, x0);
	and (d26, d27, d28);
	or (d27, d22, d25);
	or (d28, d25, d29);
	or (d29, d14, d18);
	assign f1 = d30;
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, x1, d19);
	and (d33, d2, d34);
	and (d34, d7, d35);
	and (d35, d12, d36);
	and (d36, d21, d37);
	and (d37, d38, d40);
	or (d38, x0, d39);
	or (d39, d9, d18);
	and (d40, d41, d42);
	or (d41, d25, d32);
	and (d42, d23, d43);
	or (d43, d3, d25);
	assign f2 = d44;
	and (d44, d31, d45);
	and (d45, d12, d46);
	and (d46, d21, d47);
	and (d47, d48, d49);
	or (d48, x0, d29);
	and (d49, d41, d50);
	and (d50, d43, d51);
	and (d51, d52, d53);
	or (d52, d8, d25);
	and (d53, d27, d54);
	or (d54, d25, d39);
	assign f3 = d55;
	and (d55, d31, d56);
	and (d56, d2, d57);
	and (d57, d12, d58);
	and (d58, d16, d59);
	and (d59, d27, d43);
	assign f4 = d60;
	and (d60, d2, d61);
	and (d61, d38, d62);
	and (d62, d48, d63);
	and (d63, d43, d64);
	and (d64, d27, d52);
	assign f5 = d65;
	and (d65, d12, d66);
	and (d66, d16, d67);
	and (d67, d38, d68);
	and (d68, d26, d69);
	or (d69, d17, d25);
endmodule
