//f0 = (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1913_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, x3);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d4, d9);
	or (d9, x2, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d4, d14);
	or (d14, d10, d15);
	not (d15, x2);
	and (d16, d17, d20);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d5);
	and (d20, d21, d23);
	or (d21, d18, d22);
	or (d22, x1, d9);
	and (d23, d24, d26);
	or (d24, d18, d25);
	or (d25, x1, d14);
	and (d26, d27, d28);
	or (d27, d3, d18);
	and (d28, d29, d32);
	or (d29, d18, d30);
	or (d30, d4, d31);
	or (d31, x3, d15);
	or (d32, d13, d18);
	assign f1 = d33;
	and (d33, d34, d35);
	or (d34, x0, d25);
	and (d35, d7, d36);
	and (d36, d12, d37);
	and (d37, d38, d40);
	or (d38, d18, d39);
	or (d39, x1, d31);
	and (d40, d24, d41);
	and (d41, d27, d42);
	and (d42, d28, d43);
	or (d43, d8, d18);
	assign f2 = d44;
	and (d44, d45, d46);
	or (d45, x0, d19);
	and (d46, d47, d48);
	or (d47, x0, d22);
	and (d48, d49, d50);
	or (d49, x0, d39);
	and (d50, d34, d51);
	and (d51, d7, d52);
	and (d52, d24, d53);
	or (d53, x0, d30);
	assign f3 = d54;
	and (d54, d45, d55);
	and (d55, d2, d56);
	and (d56, d53, d57);
	and (d57, d17, d58);
	and (d58, d21, d59);
	and (d59, d38, d60);
	and (d60, d27, d61);
	and (d61, d29, d43);
	assign f4 = d62;
	and (d62, d34, d63);
	and (d63, d2, d64);
	and (d64, d7, d65);
	and (d65, d12, d66);
	and (d66, d21, d32);
	assign f5 = d67;
	and (d67, d47, d68);
	and (d68, d34, d69);
	and (d69, d7, d70);
	and (d70, d53, d71);
	and (d71, d12, d72);
	and (d72, d24, d27);
	assign f6 = d73;
	and (d73, d45, d74);
	and (d74, d47, d75);
	and (d75, d7, d76);
	and (d76, d17, d77);
	and (d77, d21, d78);
	and (d78, d38, d79);
	and (d79, d24, d80);
	and (d80, d27, d32);
endmodule
