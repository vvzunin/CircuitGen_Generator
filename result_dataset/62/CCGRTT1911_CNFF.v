//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1911_CNFF(
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
	or (d8, x3, d9);
	not (d9, x2);
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d4, d13);
	not (d13, x1);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d13, d17);
	or (d17, x2, d18);
	not (d18, x3);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d13, d22);
	or (d22, d9, d18);
	and (d23, d24, d27);
	or (d24, d25, d26);
	not (d25, x0);
	or (d26, x1, d22);
	and (d27, d28, d29);
	or (d28, d16, d25);
	and (d29, d30, d32);
	or (d30, d25, d31);
	or (d31, d8, d13);
	or (d32, d21, d25);
	assign f1 = d33;
	and (d33, d2, d34);
	and (d34, d35, d36);
	or (d35, x0, d26);
	and (d36, d11, d37);
	and (d37, d38, d39);
	or (d38, d3, d25);
	and (d39, d24, d40);
	and (d40, d28, d30);
	assign f2 = d41;
	and (d41, d2, d42);
	and (d42, d43, d45);
	or (d43, x0, d44);
	or (d44, x1, d17);
	and (d45, d6, d46);
	and (d46, d35, d47);
	and (d47, d15, d48);
	and (d48, d49, d50);
	or (d49, x0, d31);
	and (d50, d38, d51);
	and (d51, d52, d53);
	or (d52, d7, d25);
	and (d53, d24, d54);
	and (d54, d27, d55);
	or (d55, d12, d25);
	assign f3 = d56;
	and (d56, d6, d57);
	and (d57, d35, d58);
	and (d58, d52, d59);
	and (d59, d32, d55);
	assign f4 = d60;
	and (d60, d43, d61);
	and (d61, d35, d62);
	and (d62, d11, d63);
	and (d63, d49, d64);
	and (d64, d38, d65);
	and (d65, d66, d67);
	or (d66, d25, d44);
	and (d67, d40, d52);
	assign f5 = d68;
	and (d68, d2, d69);
	and (d69, d11, d70);
	and (d70, d49, d71);
	and (d71, d38, d72);
	and (d72, d52, d66);
	assign f6 = d73;
	and (d73, d2, d74);
	and (d74, d43, d75);
	and (d75, d6, d76);
	and (d76, d35, d77);
	and (d77, d11, d78);
	and (d78, d38, d79);
	and (d79, d52, d80);
	and (d80, d24, d32);
endmodule
