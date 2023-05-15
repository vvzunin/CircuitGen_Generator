//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1849_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81;

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
	and (d11, x1, d12);
	and (d12, d7, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, d8);
	or (d17, d18, d19);
	and (d18, x0, d4);
	or (d19, d20, d22);
	and (d20, x0, d21);
	and (d21, d5, d12);
	or (d22, d23, d25);
	and (d23, x0, d24);
	and (d24, d5, d16);
	or (d25, d26, d28);
	and (d26, x0, d27);
	and (d27, x1, d6);
	or (d28, d29, d30);
	and (d29, x0, d11);
	and (d30, x0, d31);
	and (d31, x1, d32);
	and (d32, x2, x3);
	assign f1 = d33;
	or (d33, d2, d34);
	or (d34, d35, d36);
	and (d35, d3, d27);
	or (d36, d10, d37);
	or (d37, d14, d38);
	or (d38, d39, d40);
	and (d39, d3, d31);
	or (d40, d18, d41);
	or (d41, d29, d42);
	or (d42, d30, d43);
	and (d43, x0, d15);
	assign f2 = d44;
	or (d44, d2, d45);
	or (d45, d46, d47);
	and (d46, d3, d24);
	or (d47, d14, d48);
	or (d48, d18, d49);
	or (d49, d20, d50);
	or (d50, d25, d51);
	and (d51, x0, d52);
	and (d52, d5, d32);
	assign f3 = d53;
	or (d53, d2, d54);
	or (d54, d55, d56);
	and (d55, d3, d21);
	or (d56, d35, d57);
	or (d57, d10, d58);
	or (d58, d14, d59);
	or (d59, d18, d60);
	or (d60, d23, d61);
	or (d61, d51, d62);
	or (d62, d26, d41);
	assign f4 = d63;
	or (d63, d2, d64);
	or (d64, d55, d65);
	or (d65, d46, d66);
	or (d66, d67, d68);
	and (d67, d3, d52);
	or (d68, d35, d69);
	or (d69, d10, d70);
	or (d70, d20, d71);
	or (d71, d26, d72);
	or (d72, d29, d43);
	assign f5 = d73;
	or (d73, d55, d74);
	or (d74, d46, d75);
	or (d75, d67, d76);
	or (d76, d35, d77);
	or (d77, d10, d78);
	or (d78, d14, d79);
	or (d79, d39, d80);
	or (d80, d18, d81);
	or (d81, d20, d43);
endmodule
