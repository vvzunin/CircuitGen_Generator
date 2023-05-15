//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT578_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d4, d14);
	not (d14, x1);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d14, d18);
	or (d18, x2, d10);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d14, d22);
	or (d22, x3, d9);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d8, d14);
	and (d26, d27, d29);
	or (d27, d3, d28);
	not (d28, x0);
	and (d29, d30, d32);
	or (d30, d28, d31);
	or (d31, x1, d18);
	and (d32, d33, d35);
	or (d33, d28, d34);
	or (d34, x1, d22);
	and (d35, d36, d37);
	or (d36, d7, d28);
	or (d37, d21, d28);
	assign f1 = d38;
	and (d38, d39, d40);
	or (d39, x0, d31);
	and (d40, d6, d41);
	and (d41, d20, d42);
	and (d42, d24, d43);
	and (d43, d36, d44);
	and (d44, d37, d45);
	or (d45, d17, d28);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d12, d48);
	and (d48, d16, d49);
	and (d49, d20, d50);
	and (d50, d24, d51);
	and (d51, d30, d52);
	and (d52, d36, d53);
	or (d53, d25, d28);
	assign f3 = d54;
	and (d54, d2, d55);
	and (d55, d39, d56);
	and (d56, d57, d58);
	or (d57, x0, d34);
	and (d58, d6, d37);
	assign f4 = d59;
	and (d59, d2, d60);
	and (d60, d12, d61);
	and (d61, d16, d62);
	and (d62, d20, d63);
	and (d63, d24, d64);
	and (d64, d36, d65);
	and (d65, d45, d53);
	assign f5 = d66;
	and (d66, d39, d67);
	and (d67, d57, d68);
	and (d68, d6, d69);
	and (d69, d53, d70);
	or (d70, d13, d28);
	assign f6 = d71;
	and (d71, d39, d72);
	and (d72, d57, d73);
	and (d73, d20, d74);
	and (d74, d30, d75);
	and (d75, d33, d69);
endmodule
