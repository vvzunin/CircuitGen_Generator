//f0 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1835_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, d5);
	not (d5, x3);
	and (d6, d7, d10);
	or (d7, x0, d8);
	or (d8, d4, d9);
	not (d9, x1);
	and (d10, d11, d15);
	or (d11, x0, d12);
	or (d12, d9, d13);
	or (d13, x3, d14);
	not (d14, x2);
	and (d15, d16, d19);
	or (d16, x0, d17);
	or (d17, d9, d18);
	or (d18, d5, d14);
	and (d19, d20, d24);
	or (d20, d21, d22);
	not (d21, x0);
	or (d22, x1, d23);
	or (d23, x2, x3);
	and (d24, d25, d26);
	or (d25, d3, d21);
	and (d26, d27, d29);
	or (d27, d21, d28);
	or (d28, x1, d13);
	and (d29, d30, d32);
	or (d30, d21, d31);
	or (d31, x1, d18);
	or (d32, d21, d33);
	or (d33, d9, d23);
	assign f1 = d34;
	and (d34, d35, d36);
	or (d35, x0, d22);
	and (d36, d37, d38);
	or (d37, x0, d28);
	and (d38, d20, d39);
	and (d39, d25, d40);
	and (d40, d27, d41);
	and (d41, d42, d43);
	or (d42, d8, d21);
	and (d43, d44, d45);
	or (d44, d12, d21);
	or (d45, d17, d21);
	assign f2 = d46;
	and (d46, d2, d47);
	and (d47, d37, d48);
	and (d48, d49, d50);
	or (d49, x0, d31);
	and (d50, d7, d51);
	and (d51, d11, d52);
	and (d52, d16, d53);
	and (d53, d27, d54);
	and (d54, d30, d55);
	and (d55, d42, d44);
	assign f3 = d56;
	and (d56, d37, d57);
	and (d57, d49, d58);
	and (d58, d59, d60);
	or (d59, x0, d33);
	and (d60, d11, d61);
	and (d61, d16, d62);
	and (d62, d25, d63);
	and (d63, d27, d64);
	and (d64, d30, d65);
	and (d65, d32, d42);
	assign f4 = d66;
	and (d66, d35, d67);
	and (d67, d2, d68);
	and (d68, d37, d69);
	and (d69, d49, d70);
	and (d70, d59, d71);
	and (d71, d11, d72);
	and (d72, d20, d73);
	and (d73, d25, d74);
	and (d74, d27, d75);
	and (d75, d30, d45);
	assign f5 = d76;
	and (d76, d7, d77);
	and (d77, d16, d78);
	and (d78, d27, d55);
endmodule
