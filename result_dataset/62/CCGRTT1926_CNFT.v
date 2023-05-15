//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1926_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83, d84, d85, d86, d87, d88, d89, d90, d91;

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
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, x2, d8);
	or (d24, d25, d27);
	and (d25, d3, d26);
	and (d26, x1, d16);
	or (d27, d28, d29);
	and (d28, x0, d11);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, d5, d23);
	or (d32, d33, d34);
	and (d33, x0, d15);
	or (d34, d35, d36);
	and (d35, x0, d19);
	or (d36, d37, d39);
	and (d37, x0, d38);
	and (d38, x1, d12);
	or (d39, d40, d41);
	and (d40, x0, d22);
	and (d41, x0, d26);
	assign f1 = d42;
	or (d42, d10, d43);
	or (d43, d44, d45);
	and (d44, d3, d31);
	or (d45, d14, d46);
	or (d46, d21, d47);
	or (d47, d28, d48);
	or (d48, d30, d49);
	or (d49, d33, d40);
	assign f2 = d50;
	or (d50, d2, d51);
	or (d51, d10, d52);
	or (d52, d14, d53);
	or (d53, d54, d55);
	and (d54, d3, d38);
	or (d55, d21, d56);
	or (d56, d28, d57);
	or (d57, d30, d58);
	or (d58, d33, d59);
	or (d59, d37, d41);
	assign f3 = d60;
	or (d60, d2, d61);
	or (d61, d44, d62);
	or (d62, d14, d63);
	or (d63, d18, d64);
	or (d64, d54, d65);
	or (d65, d21, d66);
	or (d66, d67, d68);
	and (d67, x0, d4);
	or (d68, d28, d69);
	or (d69, d30, d70);
	or (d70, d33, d71);
	or (d71, d35, d59);
	assign f4 = d72;
	or (d72, d2, d73);
	or (d73, d10, d74);
	or (d74, d18, d75);
	or (d75, d25, d76);
	or (d76, d67, d77);
	or (d77, d28, d78);
	or (d78, d33, d79);
	or (d79, d35, d80);
	or (d80, d37, d40);
	assign f5 = d81;
	or (d81, d2, d82);
	or (d82, d14, d83);
	or (d83, d54, d84);
	or (d84, d21, d85);
	or (d85, d67, d86);
	or (d86, d35, d40);
	assign f6 = d87;
	or (d87, d2, d88);
	or (d88, d14, d89);
	or (d89, d25, d90);
	or (d90, d28, d91);
	or (d91, d30, d59);
endmodule
