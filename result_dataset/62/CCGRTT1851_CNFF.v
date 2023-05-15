//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1851_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, d9, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d4, d18);
	not (d18, x1);
	and (d19, d20, d24);
	or (d20, d21, d22);
	not (d21, x0);
	or (d22, x1, d23);
	or (d23, x3, d14);
	and (d24, d25, d26);
	or (d25, d17, d21);
	and (d26, d27, d29);
	or (d27, d21, d28);
	or (d28, d8, d18);
	or (d29, d21, d30);
	or (d30, d18, d23);
	assign f1 = d31;
	and (d31, d2, d32);
	and (d32, d33, d34);
	or (d33, x0, d22);
	and (d34, d11, d35);
	and (d35, d36, d37);
	or (d36, x0, d28);
	and (d37, d38, d40);
	or (d38, x0, d39);
	or (d39, d13, d18);
	and (d40, d41, d42);
	or (d41, d7, d21);
	and (d42, d20, d43);
	and (d43, d44, d45);
	or (d44, d12, d21);
	and (d45, d25, d46);
	and (d46, d27, d47);
	or (d47, d21, d39);
	assign f2 = d48;
	and (d48, d33, d49);
	and (d49, d36, d50);
	and (d50, d41, d51);
	and (d51, d20, d52);
	and (d52, d25, d44);
	assign f3 = d53;
	and (d53, d33, d54);
	and (d54, d36, d55);
	and (d55, d56, d57);
	or (d56, d3, d21);
	and (d57, d41, d58);
	and (d58, d44, d59);
	and (d59, d25, d60);
	and (d60, d29, d47);
	assign f4 = d61;
	and (d61, d6, d62);
	and (d62, d11, d63);
	and (d63, d16, d64);
	and (d64, d36, d65);
	and (d65, d66, d67);
	or (d66, x0, d30);
	and (d67, d38, d68);
	and (d68, d56, d69);
	and (d69, d41, d70);
	and (d70, d20, d71);
	and (d71, d27, d44);
	assign f5 = d72;
	and (d72, d33, d73);
	and (d73, d36, d74);
	and (d74, d66, d75);
	and (d75, d41, d76);
	and (d76, d20, d77);
	and (d77, d44, d78);
	and (d78, d25, d79);
	and (d79, d27, d60);
endmodule
