//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or not x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1918_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x2);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d20);
	or (d17, x0, d18);
	or (d18, d14, d19);
	or (d19, x3, d10);
	and (d20, d21, d24);
	or (d21, d22, d23);
	not (d22, x0);
	or (d23, x1, d15);
	and (d24, d25, d26);
	or (d25, d8, d22);
	and (d26, d27, d28);
	or (d27, d13, d22);
	and (d28, d29, d31);
	or (d29, d22, d30);
	or (d30, d4, d14);
	or (d31, d22, d32);
	or (d32, d9, d14);
	assign f1 = d33;
	and (d33, d2, d34);
	and (d34, d7, d35);
	and (d35, d12, d36);
	and (d36, d17, d37);
	and (d37, d21, d38);
	and (d38, d39, d41);
	or (d39, d22, d40);
	or (d40, x1, d19);
	and (d41, d31, d42);
	or (d42, d18, d22);
	assign f2 = d43;
	and (d43, d17, d27);
	assign f3 = d44;
	and (d44, d45, d46);
	or (d45, x0, d23);
	and (d46, d2, d47);
	and (d47, d7, d48);
	and (d48, d17, d49);
	and (d49, d50, d51);
	or (d50, x0, d32);
	and (d51, d21, d52);
	and (d52, d39, d53);
	and (d53, d25, d54);
	and (d54, d29, d42);
	assign f4 = d55;
	and (d55, d7, d56);
	and (d56, d57, d58);
	or (d57, x0, d30);
	and (d58, d21, d59);
	and (d59, d25, d60);
	and (d60, d29, d41);
	assign f5 = d61;
	and (d61, d2, d62);
	and (d62, d7, d63);
	and (d63, d17, d64);
	and (d64, d39, d65);
	and (d65, d25, d66);
	and (d66, d27, d42);
	assign f6 = d67;
	and (d67, d45, d68);
	and (d68, d2, d69);
	and (d69, d7, d70);
	and (d70, d12, d71);
	and (d71, d57, d72);
	and (d72, d17, d73);
	and (d73, d50, d74);
	and (d74, d21, d75);
	and (d75, d76, d77);
	or (d76, d3, d22);
	and (d77, d39, d78);
	and (d78, d25, d29);
endmodule
