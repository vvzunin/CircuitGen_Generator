//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1872_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d11);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, d9, d10);
	not (d9, x2);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, d10);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d8, d14);
	and (d19, d20, d22);
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d24);
	or (d23, d7, d21);
	or (d24, d13, d21);
	assign f1 = d25;
	and (d25, d26, d28);
	or (d26, x0, d27);
	or (d27, d4, d14);
	and (d28, d29, d32);
	or (d29, x0, d30);
	or (d30, d14, d31);
	or (d31, x3, d9);
	and (d32, d24, d33);
	or (d33, d21, d34);
	or (d34, x1, d15);
	assign f2 = d35;
	and (d35, d36, d37);
	or (d36, x0, d34);
	and (d37, d38, d40);
	or (d38, x0, d39);
	or (d39, x1, d31);
	and (d40, d26, d41);
	and (d41, d17, d42);
	and (d42, d23, d43);
	and (d43, d44, d45);
	or (d44, d21, d27);
	or (d45, d18, d21);
	assign f3 = d46;
	and (d46, d2, d47);
	and (d47, d36, d48);
	and (d48, d6, d49);
	and (d49, d26, d50);
	and (d50, d29, d51);
	and (d51, d17, d52);
	and (d52, d53, d54);
	or (d53, d21, d39);
	and (d54, d23, d44);
	assign f4 = d55;
	and (d55, d2, d56);
	and (d56, d36, d57);
	and (d57, d38, d58);
	and (d58, d6, d59);
	and (d59, d26, d60);
	and (d60, d29, d61);
	and (d61, d44, d53);
	assign f5 = d62;
	and (d62, d36, d63);
	and (d63, d38, d64);
	and (d64, d6, d65);
	and (d65, d26, d66);
	and (d66, d29, d67);
	and (d67, d17, d68);
	and (d68, d20, d69);
	and (d69, d23, d70);
	and (d70, d24, d44);
endmodule
