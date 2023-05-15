//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1867_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d13);
	and (d10, d3, d11);
	and (d11, d5, d12);
	and (d12, x2, d8);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, d7, x3);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d16);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d6);
	or (d29, d30, d31);
	and (d30, x0, d19);
	or (d31, d32, d34);
	and (d32, x0, d33);
	and (d33, x1, d12);
	and (d34, x0, d23);
	assign f1 = d35;
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, d5, d20);
	or (d38, d10, d39);
	or (d39, d18, d40);
	or (d40, d41, d42);
	and (d41, d3, d33);
	or (d42, d22, d43);
	or (d43, d25, d44);
	or (d44, d45, d46);
	and (d45, x0, d37);
	or (d46, d26, d47);
	and (d47, x0, d15);
	assign f2 = d48;
	or (d48, d2, d49);
	or (d49, d36, d50);
	or (d50, d10, d51);
	or (d51, d14, d52);
	or (d52, d41, d53);
	or (d53, d22, d54);
	or (d54, d25, d55);
	or (d55, d45, d56);
	or (d56, d47, d57);
	or (d57, d27, d58);
	or (d58, d30, d32);
	assign f3 = d59;
	or (d59, d10, d60);
	or (d60, d14, d61);
	or (d61, d18, d62);
	or (d62, d22, d63);
	or (d63, d25, d64);
	or (d64, d45, d65);
	or (d65, d66, d67);
	and (d66, x0, d11);
	or (d67, d47, d68);
	or (d68, d27, d31);
	assign f4 = d69;
	or (d69, d2, d70);
	or (d70, d10, d71);
	or (d71, d14, d72);
	or (d72, d73, d74);
	and (d73, d3, d28);
	or (d74, d18, d75);
	or (d75, d22, d31);
	assign f5 = d76;
	or (d76, d36, d77);
	or (d77, d10, d78);
	or (d78, d73, d79);
	or (d79, d18, d80);
	or (d80, d41, d81);
	or (d81, d25, d82);
	or (d82, d47, d58);
endmodule
