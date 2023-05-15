//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f5 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT572_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, d9, d14);
	not (d14, x3);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d18, d22);
	or (d22, x2, d14);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d8, d18);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d13, d18);
	and (d29, d30, d32);
	or (d30, d12, d31);
	not (d31, x0);
	and (d32, d33, d34);
	or (d33, d17, d31);
	or (d34, d28, d31);
	assign f1 = d35;
	and (d35, d2, d36);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, x1, d22);
	and (d39, d11, d40);
	and (d40, d16, d41);
	and (d41, d24, d42);
	and (d42, d27, d43);
	and (d43, d44, d45);
	or (d44, d3, d31);
	and (d45, d46, d47);
	or (d46, d7, d31);
	and (d47, d34, d48);
	or (d48, d21, d31);
	assign f2 = d49;
	and (d49, d44, d50);
	and (d50, d48, d51);
	and (d51, d34, d52);
	or (d52, d25, d31);
	assign f3 = d53;
	and (d53, d37, d54);
	and (d54, d6, d55);
	and (d55, d16, d56);
	and (d56, d27, d57);
	and (d57, d58, d59);
	or (d58, d31, d38);
	and (d59, d29, d46);
	assign f4 = d60;
	and (d60, d37, d61);
	and (d61, d11, d62);
	and (d62, d20, d63);
	and (d63, d27, d46);
	assign f5 = d64;
	and (d64, d16, d65);
	and (d65, d20, d66);
	and (d66, d24, d67);
	and (d67, d44, d68);
	and (d68, d58, d69);
	and (d69, d46, d48);
	assign f6 = d70;
	and (d70, d2, d71);
	and (d71, d37, d72);
	and (d72, d24, d73);
	and (d73, d27, d74);
	and (d74, d44, d75);
	and (d75, d46, d76);
	and (d76, d33, d77);
	and (d77, d48, d52);
endmodule
