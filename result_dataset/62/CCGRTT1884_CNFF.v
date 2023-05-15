//f0 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1884_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75;

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
	and (d12, d13, d15);
	or (d13, d3, d14);
	not (d14, x0);
	or (d15, d14, d16);
	or (d16, d10, d17);
	or (d17, d5, x3);
	assign f1 = d18;
	and (d18, d19, d22);
	or (d19, x0, d20);
	or (d20, d10, d21);
	or (d21, x2, x3);
	and (d22, d23, d25);
	or (d23, d14, d24);
	or (d24, x1, d21);
	and (d25, d26, d28);
	or (d26, d14, d27);
	or (d27, x1, d11);
	and (d28, d29, d31);
	or (d29, d14, d30);
	or (d30, x1, d17);
	and (d31, d13, d32);
	and (d32, d15, d33);
	or (d33, d14, d34);
	or (d34, d4, d10);
	assign f2 = d35;
	and (d35, d36, d37);
	or (d36, x0, d24);
	and (d37, d38, d39);
	or (d38, x0, d27);
	and (d39, d40, d41);
	or (d40, x0, d30);
	and (d41, d2, d42);
	and (d42, d8, d43);
	and (d43, d44, d45);
	or (d44, x0, d34);
	and (d45, d29, d46);
	and (d46, d13, d47);
	or (d47, d9, d14);
	assign f3 = d48;
	and (d48, d36, d49);
	and (d49, d38, d50);
	and (d50, d8, d51);
	and (d51, d44, d52);
	and (d52, d23, d53);
	and (d53, d26, d54);
	and (d54, d13, d29);
	assign f4 = d55;
	and (d55, d40, d56);
	and (d56, d2, d57);
	and (d57, d19, d58);
	and (d58, d59, d60);
	or (d59, x0, d16);
	and (d60, d44, d61);
	and (d61, d23, d62);
	and (d62, d26, d63);
	and (d63, d29, d64);
	and (d64, d13, d65);
	and (d65, d66, d67);
	or (d66, d14, d20);
	and (d67, d33, d47);
	assign f5 = d68;
	and (d68, d36, d69);
	and (d69, d38, d70);
	and (d70, d2, d71);
	and (d71, d19, d72);
	and (d72, d8, d73);
	and (d73, d59, d74);
	and (d74, d26, d75);
	and (d75, d15, d29);
endmodule
