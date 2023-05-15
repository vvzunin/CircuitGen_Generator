//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1900_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, x3);
	or (d12, d13, d17);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, d7, d16);
	not (d16, x2);
	or (d17, d18, d19);
	and (d18, x0, d4);
	or (d19, d20, d21);
	and (d20, x0, d10);
	or (d21, d22, d23);
	and (d22, x0, d14);
	or (d23, d24, d26);
	and (d24, x0, d25);
	and (d25, x1, d6);
	and (d26, x0, d27);
	and (d27, x1, d11);
	assign f1 = d28;
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, d5, d15);
	or (d31, d32, d35);
	and (d32, d3, d33);
	and (d33, d5, d34);
	and (d34, x3, d16);
	or (d35, d9, d36);
	or (d36, d13, d37);
	or (d37, d38, d40);
	and (d38, d3, d39);
	and (d39, x1, d34);
	or (d40, d41, d42);
	and (d41, d3, d25);
	or (d42, d22, d43);
	and (d43, d3, d27);
	assign f2 = d44;
	or (d44, d29, d45);
	or (d45, d32, d46);
	or (d46, d9, d47);
	or (d47, d13, d48);
	or (d48, d38, d49);
	or (d49, d43, d50);
	or (d50, d18, d51);
	or (d51, d26, d52);
	and (d52, x0, d39);
	assign f3 = d53;
	or (d53, d29, d36);
	assign f4 = d54;
	or (d54, d29, d55);
	or (d55, d9, d56);
	or (d56, d13, d57);
	or (d57, d41, d58);
	or (d58, d59, d60);
	and (d59, x0, d30);
	or (d60, d61, d62);
	and (d61, x0, d33);
	or (d62, d20, d63);
	or (d63, d22, d24);
	assign f5 = d64;
	or (d64, d9, d65);
	or (d65, d13, d66);
	or (d66, d43, d67);
	or (d67, d59, d68);
	or (d68, d61, d69);
	or (d69, d20, d70);
	or (d70, d22, d52);
	assign f6 = d71;
	or (d71, d29, d72);
	or (d72, d32, d73);
	or (d73, d13, d74);
	or (d74, d38, d75);
	or (d75, d17, d59);
endmodule
