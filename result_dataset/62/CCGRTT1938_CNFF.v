//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3)
//f2 = (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1938_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
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
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, x1, d18);
	or (d18, d9, d14);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d13, d22);
	not (d22, x1);
	and (d23, d24, d26);
	or (d24, d7, d25);
	not (d25, x0);
	and (d26, d27, d28);
	or (d27, d12, d25);
	or (d28, d25, d29);
	or (d29, d18, d22);
	assign f1 = d30;
	and (d30, d11, d31);
	and (d31, d27, d32);
	or (d32, x0, d29);
	assign f2 = d33;
	and (d33, d20, d34);
	and (d34, d35, d36);
	or (d35, d3, d25);
	and (d36, d24, d37);
	and (d37, d27, d38);
	and (d38, d39, d40);
	or (d39, d17, d25);
	and (d40, d28, d41);
	or (d41, d25, d42);
	or (d42, d8, d22);
	assign f3 = d43;
	and (d43, d44, d45);
	or (d44, x0, d42);
	and (d45, d20, d46);
	and (d46, d32, d47);
	and (d47, d27, d48);
	and (d48, d49, d51);
	or (d49, d25, d50);
	or (d50, d4, d22);
	and (d51, d41, d52);
	or (d52, d21, d25);
	assign f4 = d53;
	and (d53, d2, d54);
	and (d54, d6, d55);
	and (d55, d11, d56);
	and (d56, d57, d58);
	or (d57, x0, d50);
	and (d58, d44, d59);
	and (d59, d20, d60);
	and (d60, d39, d61);
	and (d61, d28, d52);
	assign f5 = d62;
	and (d62, d2, d63);
	and (d63, d6, d64);
	and (d64, d11, d65);
	and (d65, d44, d66);
	and (d66, d20, d67);
	and (d67, d32, d68);
	and (d68, d35, d69);
	and (d69, d24, d70);
	and (d70, d39, d71);
	and (d71, d40, d49);
	assign f6 = d72;
	and (d72, d6, d73);
	and (d73, d16, d74);
	and (d74, d44, d75);
	and (d75, d20, d76);
	and (d76, d35, d77);
	and (d77, d24, d78);
	and (d78, d27, d79);
	and (d79, d39, d48);
endmodule
