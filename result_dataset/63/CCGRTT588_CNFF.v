//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT588_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80;

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
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d17);
	or (d15, d7, d16);
	not (d16, x0);
	and (d17, d18, d19);
	or (d18, d12, d16);
	or (d19, d16, d20);
	or (d20, d8, d13);
	assign f1 = d21;
	and (d21, d2, d22);
	and (d22, d23, d27);
	or (d23, x0, d24);
	or (d24, x1, d25);
	or (d25, x3, d26);
	not (d26, x2);
	and (d27, d28, d31);
	or (d28, x0, d29);
	or (d29, x1, d30);
	or (d30, d9, d26);
	and (d31, d11, d32);
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, d13, d25);
	and (d35, d36, d38);
	or (d36, x0, d37);
	or (d37, d13, d30);
	and (d38, d39, d40);
	or (d39, d3, d16);
	and (d40, d41, d42);
	or (d41, d16, d24);
	or (d42, d16, d34);
	assign f2 = d43;
	and (d43, d2, d44);
	and (d44, d6, d45);
	and (d45, d23, d46);
	and (d46, d28, d47);
	and (d47, d11, d48);
	and (d48, d39, d49);
	and (d49, d41, d50);
	and (d50, d51, d52);
	or (d51, d16, d29);
	and (d52, d18, d53);
	and (d53, d19, d54);
	and (d54, d42, d55);
	or (d55, d16, d37);
	assign f3 = d56;
	and (d56, d6, d57);
	and (d57, d23, d58);
	and (d58, d11, d59);
	and (d59, d33, d60);
	and (d60, d36, d61);
	and (d61, d39, d62);
	and (d62, d15, d63);
	and (d63, d41, d64);
	and (d64, d51, d65);
	and (d65, d18, d42);
	assign f4 = d66;
	and (d66, d6, d67);
	and (d67, d68, d69);
	or (d68, x0, d20);
	and (d69, d39, d70);
	and (d70, d15, d40);
	assign f5 = d71;
	and (d71, d6, d72);
	and (d72, d23, d73);
	and (d73, d68, d74);
	and (d74, d33, d75);
	and (d75, d36, d76);
	and (d76, d39, d54);
	assign f6 = d77;
	and (d77, d23, d78);
	and (d78, d33, d79);
	and (d79, d15, d80);
	and (d80, d17, d51);
endmodule
