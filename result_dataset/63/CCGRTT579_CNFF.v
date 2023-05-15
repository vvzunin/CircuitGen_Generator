//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT579_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77;

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
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d9, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d14, d18);
	and (d22, d23, d25);
	or (d23, d8, d24);
	not (d24, x0);
	and (d25, d26, d28);
	or (d26, d24, d27);
	or (d27, d4, d18);
	or (d28, d21, d24);
	assign f1 = d29;
	and (d29, d30, d33);
	or (d30, x0, d31);
	or (d31, x1, d32);
	or (d32, x2, x3);
	and (d33, d2, d34);
	and (d34, d7, d35);
	and (d35, d12, d36);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d18, d32);
	and (d39, d20, d40);
	and (d40, d41, d42);
	or (d41, d24, d31);
	and (d42, d23, d43);
	or (d43, d17, d24);
	assign f2 = d44;
	and (d44, d30, d45);
	and (d45, d37, d46);
	and (d46, d47, d48);
	or (d47, x0, d27);
	and (d48, d16, d49);
	and (d49, d41, d50);
	and (d50, d51, d52);
	or (d51, d3, d24);
	and (d52, d23, d53);
	and (d53, d26, d54);
	or (d54, d13, d24);
	assign f3 = d55;
	and (d55, d30, d56);
	and (d56, d37, d57);
	and (d57, d16, d58);
	and (d58, d28, d59);
	or (d59, d24, d38);
	assign f4 = d60;
	and (d60, d30, d61);
	and (d61, d2, d62);
	and (d62, d47, d63);
	and (d63, d20, d64);
	and (d64, d41, d65);
	and (d65, d43, d54);
	assign f5 = d66;
	and (d66, d7, d67);
	and (d67, d37, d68);
	and (d68, d47, d69);
	and (d69, d41, d70);
	and (d70, d51, d71);
	and (d71, d28, d54);
	assign f6 = d72;
	and (d72, d2, d73);
	and (d73, d37, d74);
	and (d74, d47, d75);
	and (d75, d16, d76);
	and (d76, d54, d77);
	and (d77, d43, d59);
endmodule
