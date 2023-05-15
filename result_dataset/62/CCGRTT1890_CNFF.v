//f0 = (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1890_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, d6);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, d9, d10);
	not (d9, x0);
	or (d10, x1, d11);
	or (d11, x2, x3);
	and (d12, d13, d17);
	or (d13, d9, d14);
	or (d14, x1, d15);
	or (d15, d6, d16);
	not (d16, x2);
	and (d17, d18, d20);
	or (d18, d9, d19);
	or (d19, d4, d11);
	and (d20, d21, d22);
	or (d21, d3, d9);
	or (d22, d9, d23);
	or (d23, d4, d24);
	or (d24, x3, d16);
	assign f1 = d25;
	and (d25, d26, d28);
	or (d26, x0, d27);
	or (d27, x1, d5);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, d4, d15);
	and (d31, d13, d32);
	and (d32, d21, d33);
	or (d33, d9, d30);
	assign f2 = d34;
	and (d34, d26, d35);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, x1, d24);
	and (d38, d39, d40);
	or (d39, d9, d27);
	and (d40, d13, d41);
	and (d41, d18, d32);
	assign f3 = d42;
	and (d42, d36, d43);
	and (d43, d44, d45);
	or (d44, x0, d14);
	and (d45, d2, d46);
	and (d46, d47, d48);
	or (d47, x0, d23);
	and (d48, d29, d49);
	and (d49, d39, d50);
	and (d50, d13, d51);
	and (d51, d18, d52);
	and (d52, d21, d53);
	and (d53, d22, d33);
	assign f4 = d54;
	and (d54, d55, d56);
	or (d55, x0, d10);
	and (d56, d26, d57);
	and (d57, d2, d58);
	and (d58, d8, d59);
	and (d59, d39, d60);
	and (d60, d61, d62);
	or (d61, d9, d37);
	and (d62, d18, d21);
	assign f5 = d63;
	and (d63, d55, d64);
	and (d64, d44, d65);
	and (d65, d66, d67);
	or (d66, x0, d19);
	and (d67, d47, d68);
	and (d68, d8, d69);
	and (d69, d21, d39);
endmodule
