//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
module CCGRTT585_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80;

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
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d11);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, x2, x3);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, d5, d16);
	or (d27, d28, d29);
	and (d28, x0, d10);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, d5, d23);
	and (d32, x0, d22);
	assign f1 = d33;
	or (d33, d14, d34);
	or (d34, d35, d37);
	and (d35, d3, d36);
	and (d36, x1, d6);
	or (d37, d18, d38);
	or (d38, d21, d39);
	or (d39, d40, d41);
	and (d40, x0, d4);
	or (d41, d28, d42);
	and (d42, x0, d15);
	assign f2 = d43;
	or (d43, d44, d45);
	and (d44, d3, d26);
	or (d45, d2, d46);
	or (d46, d9, d47);
	or (d47, d48, d49);
	and (d48, d3, d31);
	or (d49, d21, d50);
	or (d50, d25, d51);
	or (d51, d40, d52);
	or (d52, d28, d53);
	or (d53, d30, d42);
	assign f3 = d54;
	or (d54, d44, d55);
	or (d55, d2, d56);
	or (d56, d48, d57);
	or (d57, d14, d58);
	or (d58, d35, d59);
	or (d59, d21, d60);
	or (d60, d40, d61);
	or (d61, d28, d62);
	or (d62, d32, d42);
	assign f4 = d63;
	or (d63, d44, d64);
	or (d64, d9, d65);
	or (d65, d48, d66);
	or (d66, d35, d67);
	or (d67, d30, d68);
	or (d68, d42, d69);
	or (d69, d32, d70);
	and (d70, x0, d36);
	assign f5 = d71;
	or (d71, d2, d72);
	or (d72, d14, d73);
	or (d73, d35, d74);
	or (d74, d21, d75);
	or (d75, d40, d76);
	or (d76, d30, d70);
	assign f6 = d77;
	or (d77, d44, d78);
	or (d78, d48, d79);
	or (d79, d35, d80);
	or (d80, d18, d52);
endmodule
