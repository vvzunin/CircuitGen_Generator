//f0 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT554_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d10);
	or (d7, x0, d8);
	or (d8, d4, d9);
	not (d9, x1);
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, d9, d13);
	or (d13, d5, d14);
	not (d14, x2);
	and (d15, d16, d20);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d19);
	or (d19, x2, x3);
	and (d20, d21, d23);
	or (d21, d17, d22);
	or (d22, x1, d13);
	and (d23, d24, d26);
	or (d24, d17, d25);
	or (d25, d9, d19);
	or (d26, d12, d17);
	assign f1 = d27;
	and (d27, d28, d29);
	or (d28, x0, d18);
	and (d29, d30, d33);
	or (d30, x0, d31);
	or (d31, x1, d32);
	or (d32, x3, d14);
	and (d33, d34, d35);
	or (d34, x0, d25);
	and (d35, d36, d37);
	or (d36, d3, d17);
	and (d37, d21, d38);
	or (d38, d17, d31);
	assign f2 = d39;
	and (d39, d28, d40);
	and (d40, d41, d42);
	or (d41, x0, d22);
	and (d42, d7, d43);
	and (d43, d11, d44);
	and (d44, d16, d45);
	and (d45, d24, d46);
	and (d46, d26, d47);
	or (d47, d8, d17);
	assign f3 = d48;
	and (d48, d2, d49);
	and (d49, d30, d50);
	and (d50, d51, d53);
	or (d51, x0, d52);
	or (d52, d9, d32);
	and (d53, d16, d54);
	and (d54, d38, d55);
	and (d55, d24, d56);
	and (d56, d47, d57);
	and (d57, d26, d58);
	or (d58, d17, d52);
	assign f4 = d59;
	and (d59, d28, d60);
	and (d60, d30, d61);
	and (d61, d41, d62);
	and (d62, d34, d63);
	and (d63, d7, d64);
	and (d64, d51, d65);
	and (d65, d16, d66);
	and (d66, d36, d67);
	and (d67, d38, d68);
	and (d68, d21, d45);
	assign f5 = d69;
	and (d69, d2, d70);
	and (d70, d41, d71);
	and (d71, d7, d72);
	and (d72, d51, d73);
	and (d73, d16, d74);
	and (d74, d36, d75);
	and (d75, d38, d76);
	and (d76, d21, d24);
endmodule
