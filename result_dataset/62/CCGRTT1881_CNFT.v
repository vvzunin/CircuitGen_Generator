//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1881_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73;

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
	and (d16, x2, x3);
	or (d17, d18, d21);
	and (d18, x0, d19);
	and (d19, d5, d20);
	and (d20, d7, d12);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, d5, d16);
	and (d24, x0, d25);
	and (d25, x1, d6);
	assign f1 = d26;
	or (d26, d9, d27);
	or (d27, d28, d29);
	and (d28, d3, d23);
	or (d29, d30, d32);
	and (d30, d3, d31);
	and (d31, x1, d11);
	or (d32, d18, d33);
	or (d33, d34, d35);
	and (d34, x0, d10);
	or (d35, d22, d36);
	or (d36, d24, d37);
	and (d37, x0, d38);
	and (d38, x1, d20);
	assign f2 = d39;
	or (d39, d2, d40);
	or (d40, d9, d41);
	or (d41, d28, d42);
	or (d42, d30, d43);
	or (d43, d44, d45);
	and (d44, x0, d4);
	or (d45, d22, d34);
	assign f3 = d46;
	or (d46, d9, d47);
	or (d47, d28, d48);
	or (d48, d49, d50);
	and (d49, d3, d38);
	or (d50, d51, d52);
	and (d51, d3, d25);
	or (d52, d18, d53);
	or (d53, d44, d54);
	or (d54, d22, d55);
	or (d55, d24, d56);
	and (d56, x0, d15);
	assign f4 = d57;
	or (d57, d58, d59);
	and (d58, d3, d19);
	or (d59, d2, d60);
	or (d60, d30, d61);
	or (d61, d14, d62);
	or (d62, d44, d63);
	or (d63, d22, d64);
	or (d64, d24, d65);
	or (d65, d56, d66);
	and (d66, x0, d31);
	assign f5 = d67;
	or (d67, d49, d68);
	or (d68, d51, d69);
	or (d69, d18, d70);
	or (d70, d44, d71);
	or (d71, d34, d72);
	or (d72, d22, d73);
	or (d73, d24, d66);
endmodule
