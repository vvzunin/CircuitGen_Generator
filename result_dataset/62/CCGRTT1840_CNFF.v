//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT1840_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76;

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
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d8, d18);
	not (d18, x1);
	and (d19, d20, d22);
	or (d20, x0, d21);
	or (d21, d13, d18);
	and (d22, d23, d26);
	or (d23, x0, d24);
	or (d24, d18, d25);
	or (d25, d9, d14);
	and (d26, d27, d29);
	or (d27, d3, d28);
	not (d28, x0);
	and (d29, d30, d31);
	or (d30, d7, d28);
	and (d31, d32, d33);
	or (d32, d12, d28);
	and (d33, d34, d36);
	or (d34, d28, d35);
	or (d35, x1, d25);
	or (d36, d24, d28);
	assign f1 = d37;
	and (d37, d6, d38);
	and (d38, d11, d39);
	and (d39, d40, d41);
	or (d40, x0, d35);
	and (d41, d20, d42);
	and (d42, d32, d43);
	and (d43, d34, d44);
	or (d44, d28, d45);
	or (d45, d4, d18);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d11, d48);
	and (d48, d40, d49);
	and (d49, d50, d51);
	or (d50, x0, d45);
	and (d51, d27, d52);
	and (d52, d30, d53);
	and (d53, d34, d54);
	and (d54, d44, d55);
	or (d55, d21, d28);
	assign f3 = d56;
	and (d56, d11, d57);
	and (d57, d16, d58);
	and (d58, d27, d59);
	and (d59, d32, d60);
	and (d60, d36, d44);
	assign f4 = d61;
	and (d61, d6, d62);
	and (d62, d11, d63);
	and (d63, d40, d64);
	and (d64, d50, d65);
	and (d65, d23, d66);
	and (d66, d30, d67);
	and (d67, d32, d68);
	and (d68, d34, d69);
	or (d69, d17, d28);
	assign f5 = d70;
	and (d70, d2, d71);
	and (d71, d11, d72);
	and (d72, d50, d73);
	and (d73, d20, d74);
	and (d74, d23, d75);
	and (d75, d27, d76);
	and (d76, d30, d42);
endmodule
