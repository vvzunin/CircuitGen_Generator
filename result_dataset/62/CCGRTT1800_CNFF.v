//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1800_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, d4, d8);
	not (d8, x1);
	and (d9, d10, d14);
	or (d10, x0, d11);
	or (d11, d8, d12);
	or (d12, x3, d13);
	not (d13, x2);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d8, d17);
	or (d17, d13, d18);
	not (d18, x3);
	and (d19, d20, d22);
	or (d20, d3, d21);
	not (d21, x0);
	and (d22, d23, d25);
	or (d23, d21, d24);
	or (d24, x1, d12);
	or (d25, d21, d26);
	or (d26, d8, d27);
	or (d27, x2, d18);
	assign f1 = d28;
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, x1, d27);
	and (d31, d32, d34);
	or (d32, x0, d33);
	or (d33, x1, d17);
	and (d34, d6, d35);
	and (d35, d20, d36);
	and (d36, d37, d38);
	or (d37, d21, d30);
	and (d38, d23, d39);
	and (d39, d40, d41);
	or (d40, d21, d33);
	and (d41, d42, d43);
	or (d42, d7, d21);
	and (d43, d25, d44);
	or (d44, d11, d21);
	assign f2 = d45;
	and (d45, d46, d47);
	or (d46, x0, d26);
	and (d47, d10, d48);
	and (d48, d15, d49);
	and (d49, d37, d50);
	and (d50, d42, d51);
	and (d51, d44, d52);
	or (d52, d16, d21);
	assign f3 = d53;
	and (d53, d2, d54);
	and (d54, d29, d55);
	and (d55, d6, d56);
	and (d56, d10, d57);
	and (d57, d15, d58);
	and (d58, d23, d59);
	and (d59, d40, d43);
	assign f4 = d60;
	and (d60, d2, d61);
	and (d61, d29, d62);
	and (d62, d32, d63);
	and (d63, d6, d64);
	and (d64, d46, d65);
	and (d65, d10, d66);
	and (d66, d37, d67);
	and (d67, d23, d68);
	and (d68, d40, d69);
	and (d69, d25, d42);
	assign f5 = d70;
	and (d70, d29, d71);
	and (d71, d72, d73);
	or (d72, x0, d24);
	and (d73, d32, d74);
	and (d74, d6, d75);
	and (d75, d46, d76);
	and (d76, d10, d77);
	and (d77, d15, d78);
	and (d78, d23, d52);
endmodule
