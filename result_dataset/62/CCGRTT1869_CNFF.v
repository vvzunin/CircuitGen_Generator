//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT1869_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73;

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
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d13, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, d7, d21);
	not (d21, x0);
	or (d22, d21, d23);
	or (d23, d4, d18);
	assign f1 = d24;
	and (d24, d6, d25);
	and (d25, d26, d29);
	or (d26, x0, d27);
	or (d27, x1, d28);
	or (d28, d9, d14);
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, d8, d18);
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, d18, d28);
	and (d35, d36, d37);
	or (d36, d3, d21);
	and (d37, d38, d39);
	or (d38, d12, d21);
	or (d39, d17, d21);
	assign f2 = d40;
	and (d40, d11, d41);
	and (d41, d42, d43);
	or (d42, x0, d23);
	and (d43, d30, d44);
	and (d44, d33, d45);
	and (d45, d20, d46);
	and (d46, d38, d47);
	and (d47, d48, d49);
	or (d48, d21, d27);
	or (d49, d21, d34);
	assign f3 = d50;
	and (d50, d6, d51);
	and (d51, d11, d52);
	and (d52, d30, d53);
	and (d53, d16, d54);
	and (d54, d33, d55);
	and (d55, d36, d56);
	and (d56, d20, d57);
	and (d57, d38, d58);
	and (d58, d48, d59);
	and (d59, d49, d60);
	or (d60, d21, d31);
	assign f4 = d61;
	and (d61, d11, d62);
	and (d62, d16, d63);
	and (d63, d36, d64);
	and (d64, d38, d65);
	and (d65, d48, d66);
	and (d66, d22, d49);
	assign f5 = d67;
	and (d67, d2, d68);
	and (d68, d11, d69);
	and (d69, d26, d70);
	and (d70, d42, d71);
	and (d71, d16, d72);
	and (d72, d33, d73);
	and (d73, d22, d38);
endmodule
