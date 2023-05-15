//f0 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
module CCGRTT1914_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, x3);
	or (d7, d8, d13);
	and (d8, d3, d9);
	and (d9, x1, d10);
	and (d10, d11, d12);
	not (d11, x2);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x3, d11);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	and (d20, x0, d19);
	assign f1 = d21;
	or (d21, d2, d22);
	or (d22, d8, d23);
	or (d23, d24, d26);
	and (d24, x0, d25);
	and (d25, d5, d16);
	or (d26, d27, d30);
	and (d27, x0, d28);
	and (d28, d5, d29);
	and (d29, x2, d12);
	or (d30, d31, d32);
	and (d31, x0, d4);
	and (d32, x0, d15);
	assign f2 = d33;
	or (d33, d8, d34);
	or (d34, d35, d37);
	and (d35, d3, d36);
	and (d36, x1, d29);
	or (d37, d27, d38);
	or (d38, d39, d40);
	and (d39, x0, d9);
	or (d40, d32, d41);
	and (d41, x0, d36);
	assign f3 = d42;
	or (d42, d43, d44);
	and (d43, d3, d25);
	or (d44, d2, d45);
	or (d45, d8, d46);
	or (d46, d14, d47);
	or (d47, d35, d48);
	or (d48, d18, d49);
	or (d49, d50, d52);
	and (d50, x0, d51);
	and (d51, d5, d10);
	or (d52, d24, d53);
	or (d53, d31, d54);
	or (d54, d20, d39);
	assign f4 = d55;
	or (d55, d43, d56);
	or (d56, d2, d57);
	or (d57, d14, d58);
	or (d58, d35, d59);
	or (d59, d50, d60);
	or (d60, d27, d61);
	or (d61, d31, d62);
	or (d62, d32, d39);
	assign f5 = d63;
	or (d63, d64, d65);
	and (d64, d3, d51);
	or (d65, d43, d66);
	or (d66, d67, d68);
	and (d67, d3, d28);
	or (d68, d2, d69);
	or (d69, d14, d70);
	or (d70, d50, d71);
	or (d71, d27, d72);
	or (d72, d31, d73);
	or (d73, d39, d74);
	or (d74, d20, d41);
	assign f6 = d75;
	or (d75, d8, d76);
	or (d76, d14, d77);
	or (d77, d35, d78);
	or (d78, d50, d79);
	or (d79, d24, d30);
endmodule
