//f0 = (x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT564_CNFF(
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
	or (d6, d7, d8);
	not (d7, x0);
	or (d8, d4, d9);
	not (d9, x1);
	assign f1 = d10;
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, x2, x3);
	and (d14, d2, d15);
	and (d15, d16, d20);
	or (d16, x0, d17);
	or (d17, x1, d18);
	or (d18, x3, d19);
	not (d19, x2);
	and (d20, d21, d22);
	or (d21, x0, d8);
	and (d22, d23, d25);
	or (d23, x0, d24);
	or (d24, d9, d18);
	and (d25, d26, d29);
	or (d26, x0, d27);
	or (d27, d9, d28);
	or (d28, d5, d19);
	and (d29, d30, d31);
	or (d30, d7, d17);
	and (d31, d32, d34);
	or (d32, d7, d33);
	or (d33, x1, d28);
	and (d34, d35, d37);
	or (d35, d7, d36);
	or (d36, d9, d13);
	or (d37, d7, d27);
	assign f2 = d38;
	and (d38, d39, d40);
	or (d39, x0, d33);
	and (d40, d41, d42);
	or (d41, x0, d36);
	and (d42, d26, d43);
	and (d43, d35, d44);
	or (d44, d7, d24);
	assign f3 = d45;
	and (d45, d2, d46);
	and (d46, d16, d47);
	and (d47, d39, d48);
	and (d48, d41, d49);
	and (d49, d26, d50);
	and (d50, d31, d51);
	or (d51, d7, d12);
	assign f4 = d52;
	and (d52, d11, d53);
	and (d53, d2, d54);
	and (d54, d39, d55);
	and (d55, d41, d56);
	and (d56, d32, d57);
	and (d57, d35, d58);
	and (d58, d6, d37);
	assign f5 = d59;
	and (d59, d11, d60);
	and (d60, d2, d61);
	and (d61, d39, d62);
	and (d62, d41, d63);
	and (d63, d23, d64);
	and (d64, d26, d65);
	and (d65, d66, d67);
	or (d66, d3, d7);
	and (d67, d30, d68);
	and (d68, d6, d35);
endmodule
