//f0 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3)
module CCGRTT1942_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d9);
	or (d6, x0, d7);
	or (d7, d4, d8);
	not (d8, x1);
	and (d9, d10, d15);
	or (d10, x0, d11);
	or (d11, d8, d12);
	or (d12, d13, d14);
	not (d13, x2);
	not (d14, x3);
	and (d15, d16, d20);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d19);
	or (d19, x3, d13);
	and (d20, d21, d23);
	or (d21, d17, d22);
	or (d22, x1, d12);
	or (d23, d17, d24);
	or (d24, d8, d25);
	or (d25, x2, d14);
	assign f1 = d26;
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, x1, d25);
	and (d29, d6, d30);
	and (d30, d31, d33);
	or (d31, x0, d32);
	or (d32, d8, d19);
	and (d33, d34, d35);
	or (d34, d17, d28);
	and (d35, d16, d36);
	and (d36, d23, d37);
	or (d37, d11, d17);
	assign f2 = d38;
	and (d38, d27, d39);
	and (d39, d40, d41);
	or (d40, x0, d18);
	and (d41, d42, d43);
	or (d42, x0, d22);
	and (d43, d6, d44);
	and (d44, d31, d45);
	and (d45, d10, d46);
	and (d46, d47, d48);
	or (d47, d3, d17);
	and (d48, d34, d49);
	and (d49, d16, d50);
	and (d50, d23, d51);
	or (d51, d17, d32);
	assign f3 = d52;
	and (d52, d27, d53);
	and (d53, d42, d54);
	and (d54, d55, d56);
	or (d55, x0, d24);
	and (d56, d47, d57);
	and (d57, d34, d58);
	and (d58, d21, d59);
	and (d59, d36, d60);
	or (d60, d7, d17);
	assign f4 = d61;
	and (d61, d2, d62);
	and (d62, d27, d63);
	and (d63, d40, d64);
	and (d64, d6, d65);
	and (d65, d55, d66);
	and (d66, d31, d67);
	and (d67, d34, d68);
	and (d68, d21, d69);
	and (d69, d23, d70);
	and (d70, d37, d51);
	assign f5 = d71;
	and (d71, d6, d72);
	and (d72, d55, d73);
	and (d73, d31, d74);
	and (d74, d10, d75);
	and (d75, d47, d76);
	and (d76, d16, d77);
	and (d77, d50, d60);
	assign f6 = d78;
	and (d78, d2, d79);
	and (d79, d42, d80);
	and (d80, d10, d31);
endmodule
