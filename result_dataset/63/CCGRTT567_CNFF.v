//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT567_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

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
	or (d13, d9, d14);
	not (d14, x1);
	and (d15, d16, d18);
	or (d16, d3, d17);
	not (d17, x0);
	and (d18, d19, d22);
	or (d19, d17, d20);
	or (d20, x1, d21);
	or (d21, d5, d10);
	and (d22, d23, d25);
	or (d23, d17, d24);
	or (d24, d4, d14);
	and (d25, d26, d27);
	or (d26, d13, d17);
	or (d27, d17, d28);
	or (d28, d14, d21);
	assign f1 = d29;
	and (d29, d7, d30);
	and (d30, d31, d34);
	or (d31, x0, d32);
	or (d32, d14, d33);
	or (d33, x2, x3);
	and (d34, d35, d36);
	or (d35, x0, d24);
	and (d36, d12, d37);
	and (d37, d38, d40);
	or (d38, d17, d39);
	or (d39, x1, d33);
	and (d40, d19, d41);
	and (d41, d42, d43);
	or (d42, d17, d32);
	and (d43, d23, d26);
	assign f2 = d44;
	and (d44, d45, d46);
	or (d45, x0, d39);
	and (d46, d31, d47);
	and (d47, d35, d48);
	and (d48, d49, d50);
	or (d49, x0, d28);
	and (d50, d38, d51);
	and (d51, d16, d52);
	and (d52, d27, d53);
	or (d53, d8, d17);
	assign f3 = d54;
	and (d54, d45, d55);
	and (d55, d2, d56);
	and (d56, d12, d57);
	and (d57, d49, d58);
	and (d58, d53, d59);
	and (d59, d19, d26);
	assign f4 = d60;
	and (d60, d7, d61);
	and (d61, d62, d63);
	or (d62, x0, d20);
	and (d63, d31, d64);
	and (d64, d12, d65);
	and (d65, d42, d66);
	and (d66, d23, d27);
	assign f5 = d67;
	and (d67, d62, d68);
	and (d68, d35, d69);
	and (d69, d12, d70);
	and (d70, d49, d71);
	and (d71, d38, d72);
	and (d72, d16, d40);
endmodule
