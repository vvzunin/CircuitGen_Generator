//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f5 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT575_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82;

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
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d11);
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, x2, x3);
	or (d20, d21, d22);
	and (d21, x0, d4);
	or (d22, d23, d25);
	and (d23, x0, d24);
	and (d24, x1, d6);
	or (d25, d26, d27);
	and (d26, x0, d15);
	and (d27, x0, d18);
	assign f1 = d28;
	or (d28, d2, d29);
	or (d29, d14, d30);
	or (d30, d17, d31);
	or (d31, d32, d35);
	and (d32, x0, d33);
	and (d33, d5, d34);
	and (d34, d7, d12);
	or (d35, d21, d36);
	or (d36, d37, d38);
	and (d37, x0, d10);
	or (d38, d39, d41);
	and (d39, x0, d40);
	and (d40, d5, d19);
	and (d41, x0, d42);
	and (d42, x1, d34);
	assign f2 = d43;
	or (d43, d44, d45);
	and (d44, d3, d33);
	or (d45, d2, d46);
	or (d46, d47, d48);
	and (d47, d3, d40);
	or (d48, d49, d50);
	and (d49, d3, d42);
	or (d50, d51, d52);
	and (d51, d3, d24);
	or (d52, d39, d53);
	or (d53, d23, d26);
	assign f3 = d54;
	or (d54, d2, d55);
	or (d55, d47, d56);
	or (d56, d51, d57);
	or (d57, d14, d58);
	or (d58, d32, d59);
	or (d59, d23, d27);
	assign f4 = d60;
	or (d60, d2, d61);
	or (d61, d9, d62);
	or (d62, d47, d63);
	or (d63, d49, d64);
	or (d64, d51, d65);
	or (d65, d17, d66);
	or (d66, d32, d67);
	or (d67, d21, d68);
	or (d68, d37, d69);
	or (d69, d23, d41);
	assign f5 = d70;
	or (d70, d9, d71);
	or (d71, d47, d72);
	or (d72, d14, d73);
	or (d73, d17, d74);
	or (d74, d32, d75);
	or (d75, d37, d76);
	or (d76, d39, d77);
	or (d77, d41, d59);
	assign f6 = d78;
	or (d78, d51, d79);
	or (d79, d14, d80);
	or (d80, d32, d81);
	or (d81, d21, d82);
	or (d82, d27, d41);
endmodule
