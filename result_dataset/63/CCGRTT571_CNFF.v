//f0 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT571_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84, d85;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, d6);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d4, d10);
	or (d10, x3, d11);
	not (d11, x2);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d4, d15);
	or (d15, d6, d11);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d5);
	and (d20, d21, d23);
	or (d21, d18, d22);
	or (d22, x1, d10);
	and (d23, d24, d26);
	or (d24, d18, d25);
	or (d25, x1, d15);
	and (d26, d27, d30);
	or (d27, d18, d28);
	or (d28, d4, d29);
	or (d29, x2, x3);
	or (d30, d3, d18);
	assign f1 = d31;
	and (d31, d32, d33);
	or (d32, x0, d19);
	and (d33, d34, d35);
	or (d34, x0, d22);
	and (d35, d2, d36);
	and (d36, d13, d37);
	and (d37, d27, d38);
	and (d38, d30, d39);
	or (d39, d14, d18);
	assign f2 = d40;
	and (d40, d41, d43);
	or (d41, x0, d42);
	or (d42, x1, d29);
	and (d43, d44, d45);
	or (d44, x0, d25);
	and (d45, d13, d46);
	and (d46, d17, d47);
	and (d47, d21, d48);
	and (d48, d24, d49);
	and (d49, d30, d50);
	or (d50, d9, d18);
	assign f3 = d51;
	and (d51, d32, d52);
	and (d52, d44, d53);
	and (d53, d8, d54);
	and (d54, d13, d55);
	and (d55, d56, d57);
	or (d56, d18, d42);
	and (d57, d17, d58);
	and (d58, d21, d59);
	and (d59, d27, d39);
	assign f4 = d60;
	and (d60, d41, d61);
	and (d61, d32, d62);
	and (d62, d34, d63);
	and (d63, d64, d65);
	or (d64, x0, d28);
	and (d65, d8, d66);
	and (d66, d13, d67);
	and (d67, d56, d68);
	and (d68, d17, d69);
	and (d69, d21, d49);
	assign f5 = d70;
	and (d70, d32, d71);
	and (d71, d44, d72);
	and (d72, d2, d73);
	and (d73, d8, d74);
	and (d74, d13, d75);
	and (d75, d20, d56);
	assign f6 = d76;
	and (d76, d41, d77);
	and (d77, d32, d78);
	and (d78, d34, d79);
	and (d79, d44, d80);
	and (d80, d64, d81);
	and (d81, d2, d82);
	and (d82, d8, d83);
	and (d83, d13, d84);
	and (d84, d17, d85);
	and (d85, d21, d27);
endmodule
