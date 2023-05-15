//f0 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1896_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, d9, d10);
	not (d9, x1);
	or (d10, x2, x3);
	and (d11, d12, d14);
	or (d12, x0, d13);
	or (d13, d4, d9);
	and (d14, d15, d20);
	or (d15, d16, d17);
	not (d16, x0);
	or (d17, x1, d18);
	or (d18, x2, d19);
	not (d19, x3);
	and (d20, d21, d24);
	or (d21, d16, d22);
	or (d22, x1, d23);
	or (d23, d5, d19);
	or (d24, d16, d25);
	or (d25, d9, d23);
	assign f1 = d26;
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, x1, d10);
	and (d29, d30, d31);
	or (d30, x0, d17);
	and (d31, d7, d32);
	and (d32, d33, d34);
	or (d33, d16, d28);
	and (d34, d15, d35);
	and (d35, d36, d37);
	or (d36, d3, d16);
	and (d37, d21, d38);
	and (d38, d24, d39);
	or (d39, d8, d16);
	assign f2 = d40;
	and (d40, d27, d41);
	and (d41, d30, d42);
	and (d42, d2, d43);
	and (d43, d44, d45);
	or (d44, x0, d22);
	and (d45, d7, d46);
	and (d46, d47, d49);
	or (d47, x0, d48);
	or (d48, d9, d18);
	and (d49, d33, d35);
	assign f3 = d50;
	and (d50, d27, d51);
	and (d51, d44, d52);
	and (d52, d47, d53);
	and (d53, d12, d54);
	and (d54, d55, d56);
	or (d55, x0, d25);
	and (d56, d33, d57);
	and (d57, d21, d58);
	and (d58, d39, d59);
	and (d59, d60, d61);
	or (d60, d16, d48);
	or (d61, d13, d16);
	assign f4 = d62;
	and (d62, d30, d63);
	and (d63, d47, d64);
	and (d64, d12, d65);
	and (d65, d33, d66);
	and (d66, d36, d67);
	and (d67, d21, d60);
	assign f5 = d68;
	and (d68, d27, d69);
	and (d69, d30, d70);
	and (d70, d7, d71);
	and (d71, d12, d72);
	and (d72, d33, d73);
	and (d73, d36, d74);
	and (d74, d21, d75);
	and (d75, d24, d60);
endmodule
