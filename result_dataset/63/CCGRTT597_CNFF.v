//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT597_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81;

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
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, d5, d10);
	and (d16, d17, d19);
	or (d17, d3, d18);
	not (d18, x0);
	and (d19, d20, d22);
	or (d20, d18, d21);
	or (d21, x1, d15);
	or (d22, d13, d18);
	assign f1 = d23;
	and (d23, d24, d27);
	or (d24, x0, d25);
	or (d25, x1, d26);
	or (d26, x2, x3);
	and (d27, d2, d28);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, d14, d26);
	and (d31, d32, d33);
	or (d32, d18, d25);
	and (d33, d17, d34);
	and (d34, d19, d35);
	or (d35, d8, d18);
	assign f2 = d36;
	and (d36, d24, d37);
	and (d37, d2, d38);
	and (d38, d7, d39);
	and (d39, d40, d41);
	or (d40, x0, d21);
	and (d41, d29, d42);
	and (d42, d43, d45);
	or (d43, x0, d44);
	or (d44, d9, d14);
	and (d45, d17, d46);
	and (d46, d47, d49);
	or (d47, d18, d48);
	or (d48, d4, d14);
	and (d49, d22, d50);
	or (d50, d18, d44);
	assign f3 = d51;
	and (d51, d24, d52);
	and (d52, d7, d53);
	and (d53, d40, d54);
	and (d54, d29, d55);
	and (d55, d56, d57);
	or (d56, x0, d48);
	and (d57, d43, d58);
	and (d58, d17, d59);
	and (d59, d20, d50);
	assign f4 = d60;
	and (d60, d24, d61);
	and (d61, d7, d62);
	and (d62, d40, d63);
	and (d63, d29, d64);
	and (d64, d43, d65);
	and (d65, d17, d66);
	and (d66, d35, d67);
	and (d67, d20, d68);
	and (d68, d22, d47);
	assign f5 = d69;
	and (d69, d2, d70);
	and (d70, d40, d71);
	and (d71, d43, d72);
	and (d72, d12, d73);
	and (d73, d17, d74);
	and (d74, d35, d75);
	and (d75, d20, d76);
	and (d76, d47, d50);
	assign f6 = d77;
	and (d77, d24, d78);
	and (d78, d7, d79);
	and (d79, d40, d80);
	and (d80, d43, d81);
	and (d81, d17, d76);
endmodule
