//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1902_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84, d85;

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
	and (d12, d7, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, d8);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, d5, d20);
	and (d20, x2, x3);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d6);
	or (d24, d25, d26);
	and (d25, x0, d15);
	or (d26, d27, d28);
	and (d27, x0, d19);
	or (d28, d29, d31);
	and (d29, x0, d30);
	and (d30, x1, d12);
	or (d31, d32, d34);
	and (d32, x0, d33);
	and (d33, x1, d16);
	and (d34, x0, d35);
	and (d35, x1, d20);
	assign f1 = d36;
	or (d36, d2, d37);
	or (d37, d10, d38);
	or (d38, d18, d39);
	or (d39, d22, d40);
	or (d40, d41, d42);
	and (d41, d3, d30);
	or (d42, d43, d44);
	and (d43, d3, d35);
	or (d44, d25, d45);
	or (d45, d27, d46);
	or (d46, d28, d47);
	and (d47, x0, d23);
	assign f2 = d48;
	or (d48, d2, d49);
	or (d49, d41, d50);
	or (d50, d43, d51);
	or (d51, d52, d53);
	and (d52, x0, d11);
	or (d53, d27, d54);
	or (d54, d47, d55);
	or (d55, d29, d32);
	assign f3 = d56;
	or (d56, d14, d57);
	or (d57, d22, d58);
	or (d58, d41, d59);
	or (d59, d60, d61);
	and (d60, d3, d33);
	or (d61, d62, d63);
	and (d62, x0, d4);
	or (d63, d52, d64);
	or (d64, d25, d65);
	or (d65, d27, d32);
	assign f4 = d66;
	or (d66, d2, d67);
	or (d67, d10, d68);
	or (d68, d14, d69);
	or (d69, d18, d70);
	or (d70, d22, d71);
	or (d71, d60, d72);
	or (d72, d52, d73);
	or (d73, d25, d47);
	assign f5 = d74;
	or (d74, d18, d75);
	or (d75, d22, d76);
	or (d76, d41, d77);
	or (d77, d60, d78);
	or (d78, d43, d79);
	or (d79, d62, d80);
	or (d80, d52, d81);
	or (d81, d25, d31);
	assign f6 = d82;
	or (d82, d10, d83);
	or (d83, d18, d84);
	or (d84, d43, d85);
	or (d85, d44, d52);
endmodule
