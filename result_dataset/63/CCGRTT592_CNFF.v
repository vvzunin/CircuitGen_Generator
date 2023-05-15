//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT592_CNFF(
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
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d8, d18);
	and (d22, d23, d25);
	or (d23, x0, d24);
	or (d24, d13, d18);
	and (d25, d26, d28);
	or (d26, d3, d27);
	not (d27, x0);
	and (d28, d29, d30);
	or (d29, d17, d27);
	and (d30, d31, d34);
	or (d31, d27, d32);
	or (d32, d18, d33);
	or (d33, x2, d14);
	and (d34, d35, d36);
	or (d35, d21, d27);
	or (d36, d24, d27);
	assign f1 = d37;
	and (d37, d2, d38);
	and (d38, d11, d39);
	and (d39, d40, d41);
	or (d40, x0, d32);
	and (d41, d20, d42);
	and (d42, d43, d44);
	or (d43, d12, d27);
	and (d44, d29, d45);
	and (d45, d31, d35);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d6, d48);
	and (d48, d40, d49);
	and (d49, d20, d50);
	and (d50, d23, d51);
	and (d51, d26, d52);
	and (d52, d29, d34);
	assign f3 = d53;
	and (d53, d40, d54);
	and (d54, d20, d55);
	and (d55, d36, d56);
	or (d56, d7, d27);
	assign f4 = d57;
	and (d57, d11, d58);
	and (d58, d16, d59);
	and (d59, d40, d60);
	and (d60, d23, d61);
	and (d61, d56, d62);
	or (d62, d27, d63);
	or (d63, x1, d33);
	assign f5 = d64;
	and (d64, d65, d66);
	or (d65, x0, d63);
	and (d66, d20, d67);
	and (d67, d23, d68);
	and (d68, d62, d69);
	and (d69, d56, d70);
	and (d70, d43, d71);
	and (d71, d29, d36);
	assign f6 = d72;
	and (d72, d65, d73);
	and (d73, d6, d74);
	and (d74, d16, d75);
	and (d75, d40, d76);
	and (d76, d62, d77);
	and (d77, d45, d56);
endmodule
