//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1924_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d13);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, d12);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, d7, d12);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, x2, x3);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, d5, d16);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d28);
	and (d27, x0, d10);
	or (d28, d29, d31);
	and (d29, x0, d30);
	and (d30, d5, d20);
	or (d31, d32, d33);
	and (d32, x0, d15);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, x1, d6);
	and (d36, x0, d37);
	and (d37, x1, d11);
	assign f1 = d38;
	or (d38, d39, d40);
	and (d39, d3, d23);
	or (d40, d2, d41);
	or (d41, d42, d43);
	and (d42, d3, d30);
	or (d43, d22, d44);
	or (d44, d25, d45);
	or (d45, d27, d46);
	or (d46, d29, d33);
	assign f2 = d47;
	or (d47, d39, d48);
	or (d48, d2, d49);
	or (d49, d42, d50);
	or (d50, d51, d52);
	and (d51, d3, d35);
	or (d52, d18, d53);
	or (d53, d22, d54);
	or (d54, d25, d27);
	assign f3 = d55;
	or (d55, d39, d56);
	or (d56, d2, d57);
	or (d57, d51, d58);
	or (d58, d59, d60);
	and (d59, d3, d37);
	or (d60, d27, d29);
	assign f4 = d61;
	or (d61, d39, d62);
	or (d62, d14, d63);
	or (d63, d51, d64);
	or (d64, d18, d65);
	or (d65, d25, d66);
	or (d66, d32, d67);
	or (d67, d36, d68);
	and (d68, x0, d19);
	assign f5 = d69;
	or (d69, d39, d70);
	or (d70, d2, d71);
	or (d71, d14, d72);
	or (d72, d59, d73);
	or (d73, d25, d74);
	or (d74, d29, d36);
	assign f6 = d75;
	or (d75, d39, d76);
	or (d76, d9, d77);
	or (d77, d14, d78);
	or (d78, d51, d79);
	or (d79, d18, d80);
	or (d80, d27, d81);
	or (d81, d34, d67);
endmodule
