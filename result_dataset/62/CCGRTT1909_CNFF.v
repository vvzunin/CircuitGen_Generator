//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
module CCGRTT1909_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83;

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
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, x1, d13);
	or (d13, d9, d14);
	not (d14, x3);
	and (d15, d16, d20);
	or (d16, x0, d17);
	or (d17, d18, d19);
	not (d18, x1);
	or (d19, x2, d14);
	and (d20, d21, d23);
	or (d21, x0, d22);
	or (d22, d8, d18);
	and (d23, d24, d26);
	or (d24, d3, d25);
	not (d25, x0);
	and (d26, d27, d28);
	or (d27, d7, d25);
	and (d28, d29, d30);
	or (d29, d12, d25);
	or (d30, d25, d31);
	or (d31, d13, d18);
	assign f1 = d32;
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, x1, d19);
	and (d35, d6, d36);
	and (d36, d37, d39);
	or (d37, x0, d38);
	or (d38, d4, d18);
	and (d39, d24, d40);
	and (d40, d27, d41);
	and (d41, d29, d42);
	and (d42, d43, d44);
	or (d43, d25, d38);
	or (d44, d17, d25);
	assign f2 = d45;
	and (d45, d33, d46);
	and (d46, d11, d47);
	and (d47, d37, d48);
	and (d48, d49, d50);
	or (d49, x0, d31);
	and (d50, d24, d51);
	and (d51, d52, d53);
	or (d52, d25, d34);
	and (d53, d27, d54);
	and (d54, d30, d43);
	assign f3 = d55;
	and (d55, d2, d56);
	and (d56, d33, d57);
	and (d57, d6, d58);
	and (d58, d11, d59);
	and (d59, d37, d60);
	and (d60, d21, d61);
	and (d61, d49, d62);
	and (d62, d52, d63);
	and (d63, d27, d64);
	and (d64, d43, d65);
	and (d65, d44, d66);
	or (d66, d22, d25);
	assign f4 = d67;
	and (d67, d6, d68);
	and (d68, d16, d69);
	and (d69, d24, d70);
	and (d70, d52, d71);
	and (d71, d30, d44);
	assign f5 = d72;
	and (d72, d2, d73);
	and (d73, d33, d74);
	and (d74, d37, d75);
	and (d75, d16, d76);
	and (d76, d21, d77);
	and (d77, d49, d78);
	and (d78, d52, d64);
	assign f6 = d79;
	and (d79, d2, d80);
	and (d80, d33, d81);
	and (d81, d37, d82);
	and (d82, d21, d83);
	and (d83, d27, d29);
endmodule
