//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT594_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

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
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d10, d15);
	or (d15, d5, x3);
	and (d16, d17, d19);
	or (d17, d9, d18);
	not (d18, x0);
	or (d19, d14, d18);
	assign f1 = d20;
	and (d20, d21, d24);
	or (d21, x0, d22);
	or (d22, x1, d23);
	or (d23, x2, x3);
	and (d24, d2, d25);
	and (d25, d26, d27);
	or (d26, d18, d22);
	and (d27, d28, d30);
	or (d28, d18, d29);
	or (d29, x1, d15);
	and (d30, d16, d31);
	or (d31, d3, d18);
	assign f2 = d32;
	and (d32, d21, d33);
	and (d33, d34, d35);
	or (d34, x0, d29);
	and (d35, d13, d36);
	and (d36, d27, d37);
	or (d37, d18, d38);
	or (d38, x1, d11);
	assign f3 = d39;
	and (d39, d34, d40);
	and (d40, d2, d41);
	and (d41, d42, d44);
	or (d42, x0, d43);
	or (d43, d10, d23);
	and (d44, d8, d45);
	and (d45, d26, d46);
	and (d46, d37, d47);
	and (d47, d28, d48);
	and (d48, d16, d49);
	or (d49, d18, d43);
	assign f4 = d50;
	and (d50, d51, d52);
	or (d51, x0, d38);
	and (d52, d42, d53);
	and (d53, d13, d54);
	and (d54, d55, d57);
	or (d55, x0, d56);
	or (d56, d4, d10);
	and (d57, d26, d58);
	and (d58, d37, d59);
	and (d59, d31, d60);
	and (d60, d17, d61);
	or (d61, d18, d56);
	assign f5 = d62;
	and (d62, d2, d63);
	and (d63, d42, d64);
	and (d64, d13, d65);
	and (d65, d55, d66);
	and (d66, d28, d61);
	assign f6 = d67;
	and (d67, d51, d68);
	and (d68, d13, d69);
	and (d69, d28, d70);
	and (d70, d17, d31);
endmodule
