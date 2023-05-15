//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1802_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d12);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, d5, d11);
	not (d11, x3);
	and (d12, d13, d16);
	or (d13, d14, d15);
	not (d14, x0);
	or (d15, x1, d10);
	and (d16, d17, d20);
	or (d17, d14, d18);
	or (d18, d9, d19);
	or (d19, x2, d11);
	or (d20, d8, d14);
	assign f1 = d21;
	and (d21, d22, d25);
	or (d22, x0, d23);
	or (d23, x1, d24);
	or (d24, x2, x3);
	and (d25, d2, d26);
	and (d26, d27, d28);
	or (d27, x0, d15);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, d9, d24);
	and (d31, d32, d33);
	or (d32, x0, d18);
	and (d33, d7, d34);
	and (d34, d35, d36);
	or (d35, d14, d23);
	and (d36, d37, d39);
	or (d37, d14, d38);
	or (d38, x1, d19);
	and (d39, d40, d41);
	or (d40, d3, d14);
	and (d41, d13, d42);
	and (d42, d43, d44);
	or (d43, d14, d30);
	and (d44, d17, d45);
	and (d45, d20, d46);
	or (d46, d14, d47);
	or (d47, d4, d9);
	assign f2 = d48;
	and (d48, d2, d49);
	and (d49, d29, d50);
	and (d50, d32, d51);
	and (d51, d52, d53);
	or (d52, x0, d47);
	and (d53, d35, d54);
	and (d54, d13, d20);
	assign f3 = d55;
	and (d55, d56, d57);
	or (d56, x0, d38);
	and (d57, d27, d58);
	and (d58, d29, d59);
	and (d59, d32, d60);
	and (d60, d35, d61);
	and (d61, d37, d62);
	and (d62, d20, d40);
	assign f4 = d63;
	and (d63, d2, d64);
	and (d64, d27, d65);
	and (d65, d29, d66);
	and (d66, d7, d67);
	and (d67, d40, d43);
	assign f5 = d68;
	and (d68, d22, d69);
	and (d69, d56, d70);
	and (d70, d27, d71);
	and (d71, d29, d72);
	and (d72, d7, d73);
	and (d73, d37, d74);
	and (d74, d13, d46);
endmodule
