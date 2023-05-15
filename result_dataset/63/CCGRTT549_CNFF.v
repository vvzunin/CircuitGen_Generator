//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT549_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80;

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
	and (d15, d16, d20);
	or (d16, x0, d17);
	or (d17, d18, d19);
	not (d18, x1);
	or (d19, x2, x3);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d4, d18);
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, d9, d18);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, d14, d18);
	and (d29, d30, d33);
	or (d30, d31, d32);
	not (d31, x0);
	or (d32, x1, d19);
	and (d33, d34, d35);
	or (d34, d3, d31);
	and (d35, d36, d37);
	or (d36, d22, d31);
	or (d37, d25, d31);
	assign f1 = d38;
	and (d38, d2, d39);
	and (d39, d7, d40);
	and (d40, d12, d41);
	and (d41, d16, d42);
	and (d42, d21, d43);
	and (d43, d24, d44);
	and (d44, d27, d45);
	and (d45, d34, d46);
	and (d46, d47, d48);
	or (d47, d8, d31);
	and (d48, d36, d49);
	and (d49, d37, d50);
	or (d50, d28, d31);
	assign f2 = d51;
	and (d51, d2, d52);
	and (d52, d49, d53);
	or (d53, d17, d31);
	assign f3 = d54;
	and (d54, d2, d55);
	and (d55, d12, d56);
	and (d56, d16, d57);
	and (d57, d24, d58);
	and (d58, d30, d59);
	and (d59, d34, d60);
	and (d60, d47, d61);
	and (d61, d53, d62);
	and (d62, d36, d50);
	assign f4 = d63;
	and (d63, d64, d65);
	or (d64, x0, d32);
	and (d65, d12, d66);
	and (d66, d16, d67);
	and (d67, d27, d68);
	and (d68, d34, d69);
	and (d69, d47, d70);
	and (d70, d62, d71);
	or (d71, d13, d31);
	assign f5 = d72;
	and (d72, d64, d73);
	and (d73, d2, d74);
	and (d74, d12, d75);
	and (d75, d16, d76);
	and (d76, d21, d77);
	and (d77, d24, d78);
	and (d78, d47, d79);
	and (d79, d71, d80);
	and (d80, d50, d53);
endmodule
