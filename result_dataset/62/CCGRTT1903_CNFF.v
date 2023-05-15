//f0 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f6 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1903_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75;

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
	and (d11, d12, d15);
	or (d12, x0, d13);
	or (d13, d9, d14);
	not (d14, x1);
	and (d15, d16, d20);
	or (d16, d17, d18);
	not (d17, x0);
	or (d18, x1, d19);
	or (d19, x2, x3);
	and (d20, d21, d22);
	or (d21, d8, d17);
	and (d22, d23, d25);
	or (d23, d17, d24);
	or (d24, d4, d14);
	and (d25, d26, d29);
	or (d26, d17, d27);
	or (d27, d14, d28);
	or (d28, x3, d10);
	or (d29, d13, d17);
	assign f1 = d30;
	and (d30, d31, d32);
	or (d31, x0, d18);
	and (d32, d33, d35);
	or (d33, x0, d34);
	or (d34, d14, d19);
	and (d35, d12, d36);
	and (d36, d16, d37);
	and (d37, d38, d39);
	or (d38, d3, d17);
	and (d39, d21, d29);
	assign f2 = d40;
	and (d40, d31, d41);
	and (d41, d2, d42);
	and (d42, d7, d43);
	and (d43, d33, d44);
	and (d44, d45, d46);
	or (d45, x0, d24);
	and (d46, d47, d48);
	or (d47, x0, d27);
	and (d48, d16, d49);
	and (d49, d21, d50);
	or (d50, d17, d34);
	assign f3 = d51;
	and (d51, d31, d52);
	and (d52, d2, d53);
	and (d53, d7, d54);
	and (d54, d33, d37);
	assign f4 = d55;
	and (d55, d56, d58);
	or (d56, x0, d57);
	or (d57, x1, d28);
	and (d58, d33, d59);
	and (d59, d47, d60);
	and (d60, d38, d61);
	and (d61, d21, d62);
	and (d62, d23, d29);
	assign f5 = d63;
	and (d63, d2, d64);
	and (d64, d56, d65);
	and (d65, d45, d66);
	and (d66, d21, d23);
	assign f6 = d67;
	and (d67, d31, d68);
	and (d68, d2, d69);
	and (d69, d56, d70);
	and (d70, d7, d71);
	and (d71, d45, d72);
	and (d72, d12, d73);
	and (d73, d16, d74);
	and (d74, d21, d75);
	and (d75, d50, d62);
endmodule
