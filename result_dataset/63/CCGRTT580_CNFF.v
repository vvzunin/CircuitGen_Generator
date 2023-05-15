//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT580_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76;

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
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x3, d9);
	or (d20, d21, d22);
	not (d21, x0);
	or (d22, d8, d14);
	assign f1 = d23;
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, x1, d19);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d4, d14);
	and (d29, d12, d30);
	and (d30, d17, d31);
	and (d31, d32, d33);
	or (d32, x0, d22);
	and (d33, d20, d34);
	or (d34, d21, d28);
	assign f2 = d35;
	and (d35, d24, d36);
	and (d36, d27, d37);
	and (d37, d17, d38);
	and (d38, d39, d40);
	or (d39, d7, d21);
	and (d40, d34, d41);
	and (d41, d42, d43);
	or (d42, d13, d21);
	and (d43, d20, d44);
	or (d44, d18, d21);
	assign f3 = d45;
	and (d45, d24, d46);
	and (d46, d6, d47);
	and (d47, d27, d48);
	and (d48, d32, d49);
	and (d49, d50, d51);
	or (d50, d3, d21);
	and (d51, d40, d52);
	or (d52, d21, d53);
	or (d53, x1, d15);
	assign f4 = d54;
	and (d54, d55, d56);
	or (d55, x0, d53);
	and (d56, d24, d57);
	and (d57, d6, d58);
	and (d58, d17, d59);
	and (d59, d50, d60);
	and (d60, d61, d62);
	or (d61, d21, d25);
	and (d62, d39, d42);
	assign f5 = d63;
	and (d63, d24, d64);
	and (d64, d6, d65);
	and (d65, d12, d66);
	and (d66, d32, d67);
	and (d67, d50, d68);
	and (d68, d61, d69);
	and (d69, d34, d70);
	and (d70, d20, d42);
	assign f6 = d71;
	and (d71, d55, d72);
	and (d72, d6, d73);
	and (d73, d17, d74);
	and (d74, d50, d75);
	and (d75, d52, d76);
	and (d76, d34, d39);
endmodule
