//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1809_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x3, d9);
	not (d9, x2);
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d17);
	or (d15, x0, d16);
	or (d16, d8, d13);
	and (d17, d18, d23);
	or (d18, d19, d20);
	not (d19, x0);
	or (d20, x1, d21);
	or (d21, x2, d22);
	not (d22, x3);
	and (d23, d24, d25);
	or (d24, d7, d19);
	and (d25, d26, d29);
	or (d26, d19, d27);
	or (d27, x1, d28);
	or (d28, d9, d22);
	and (d29, d30, d31);
	or (d30, d12, d19);
	or (d31, d19, d32);
	or (d32, d13, d28);
	assign f1 = d33;
	and (d33, d6, d34);
	and (d34, d11, d35);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d13, d21);
	and (d38, d15, d39);
	and (d39, d23, d40);
	or (d40, d3, d19);
	assign f2 = d41;
	and (d41, d2, d42);
	and (d42, d43, d44);
	or (d43, x0, d20);
	and (d44, d15, d45);
	and (d45, d46, d47);
	or (d46, x0, d32);
	and (d47, d40, d48);
	and (d48, d18, d49);
	and (d49, d30, d50);
	and (d50, d31, d51);
	or (d51, d19, d37);
	assign f3 = d52;
	and (d52, d2, d53);
	and (d53, d43, d54);
	and (d54, d55, d56);
	or (d55, x0, d27);
	and (d56, d11, d57);
	and (d57, d46, d58);
	and (d58, d26, d30);
	assign f4 = d59;
	and (d59, d2, d60);
	and (d60, d43, d61);
	and (d61, d55, d62);
	and (d62, d46, d63);
	and (d63, d40, d64);
	and (d64, d18, d65);
	and (d65, d24, d66);
	and (d66, d26, d67);
	and (d67, d30, d51);
	assign f5 = d68;
	and (d68, d2, d69);
	and (d69, d43, d70);
	and (d70, d6, d71);
	and (d71, d55, d72);
	and (d72, d15, d73);
	and (d73, d46, d74);
	and (d74, d40, d75);
	and (d75, d24, d76);
	and (d76, d26, d50);
endmodule
