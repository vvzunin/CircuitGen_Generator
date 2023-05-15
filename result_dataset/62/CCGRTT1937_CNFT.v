//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1937_CNFT(
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
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, x2, x3);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d28);
	and (d27, x0, d11);
	or (d28, d29, d30);
	and (d29, x0, d15);
	or (d30, d31, d33);
	and (d31, x0, d32);
	and (d32, d5, d23);
	or (d33, d34, d35);
	and (d34, x0, d19);
	and (d35, x0, d22);
	assign f1 = d36;
	or (d36, d10, d37);
	or (d37, d14, d38);
	or (d38, d18, d39);
	or (d39, d40, d42);
	and (d40, d3, d41);
	and (d41, x1, d12);
	or (d42, d43, d45);
	and (d43, d3, d44);
	and (d44, x1, d16);
	or (d45, d21, d46);
	or (d46, d27, d33);
	assign f2 = d47;
	or (d47, d10, d48);
	or (d48, d49, d50);
	and (d49, d3, d32);
	or (d50, d18, d51);
	or (d51, d40, d52);
	or (d52, d21, d53);
	or (d53, d25, d33);
	assign f3 = d54;
	or (d54, d2, d55);
	or (d55, d10, d56);
	or (d56, d43, d57);
	or (d57, d21, d58);
	or (d58, d31, d35);
	assign f4 = d59;
	or (d59, d2, d60);
	or (d60, d14, d61);
	or (d61, d49, d62);
	or (d62, d40, d63);
	or (d63, d29, d64);
	or (d64, d34, d65);
	and (d65, x0, d44);
	assign f5 = d66;
	or (d66, d2, d67);
	or (d67, d10, d68);
	or (d68, d14, d69);
	or (d69, d40, d70);
	or (d70, d25, d71);
	or (d71, d27, d72);
	or (d72, d31, d73);
	or (d73, d34, d74);
	or (d74, d65, d75);
	and (d75, x0, d41);
	assign f6 = d76;
	or (d76, d2, d77);
	or (d77, d14, d78);
	or (d78, d49, d79);
	or (d79, d18, d80);
	or (d80, d40, d81);
	or (d81, d21, d82);
	or (d82, d25, d83);
	or (d83, d27, d84);
	or (d84, d34, d85);
	or (d85, d35, d65);
endmodule
