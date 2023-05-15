//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1825_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, d11);
	not (d11, x3);
	and (d12, d13, d15);
	or (d13, x0, d14);
	or (d14, d4, d9);
	and (d15, d16, d18);
	or (d16, d3, d17);
	not (d17, x0);
	and (d18, d19, d22);
	or (d19, d17, d20);
	or (d20, x1, d21);
	or (d21, d5, d11);
	and (d22, d23, d24);
	or (d23, d8, d17);
	and (d24, d25, d26);
	or (d25, d14, d17);
	or (d26, d17, d27);
	or (d27, d9, d21);
	assign f1 = d28;
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, x1, d10);
	and (d31, d2, d32);
	and (d32, d7, d33);
	and (d33, d13, d34);
	and (d34, d35, d36);
	or (d35, x0, d27);
	and (d36, d37, d40);
	or (d37, d17, d38);
	or (d38, x1, d39);
	or (d39, x2, x3);
	and (d40, d41, d42);
	or (d41, d17, d30);
	and (d42, d16, d25);
	assign f2 = d43;
	and (d43, d44, d45);
	or (d44, x0, d38);
	and (d45, d2, d46);
	and (d46, d13, d47);
	and (d47, d35, d48);
	and (d48, d37, d49);
	and (d49, d16, d50);
	and (d50, d19, d51);
	or (d51, d17, d52);
	or (d52, d9, d39);
	assign f3 = d53;
	and (d53, d2, d54);
	and (d54, d7, d55);
	and (d55, d19, d56);
	and (d56, d51, d57);
	and (d57, d23, d25);
	assign f4 = d58;
	and (d58, d44, d59);
	and (d59, d60, d61);
	or (d60, x0, d20);
	and (d61, d62, d63);
	or (d62, x0, d52);
	and (d63, d7, d64);
	and (d64, d35, d65);
	and (d65, d41, d66);
	and (d66, d16, d19);
	assign f5 = d67;
	and (d67, d44, d68);
	and (d68, d60, d69);
	and (d69, d37, d70);
	and (d70, d41, d71);
	and (d71, d16, d72);
	and (d72, d19, d23);
endmodule
