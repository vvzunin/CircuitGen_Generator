//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3)
module CCGRTT1930_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

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
	or (d17, d18, d19);
	and (d18, x0, d4);
	or (d19, d20, d23);
	and (d20, x0, d21);
	and (d21, d5, d22);
	and (d22, x2, x3);
	or (d23, d24, d26);
	and (d24, x0, d25);
	and (d25, x1, d6);
	and (d26, x0, d27);
	and (d27, x1, d11);
	assign f1 = d28;
	or (d28, d2, d29);
	or (d29, d9, d30);
	or (d30, d31, d32);
	and (d31, d3, d21);
	or (d32, d18, d33);
	or (d33, d24, d34);
	or (d34, d26, d35);
	and (d35, x0, d36);
	and (d36, x1, d22);
	assign f2 = d37;
	or (d37, d2, d38);
	or (d38, d39, d40);
	and (d39, x0, d10);
	or (d40, d23, d41);
	and (d41, x0, d15);
	assign f3 = d42;
	or (d42, d2, d43);
	or (d43, d31, d44);
	or (d44, d14, d45);
	or (d45, d46, d47);
	and (d46, d3, d25);
	or (d47, d48, d49);
	and (d48, d3, d36);
	or (d49, d18, d50);
	or (d50, d39, d51);
	or (d51, d26, d41);
	assign f4 = d52;
	or (d52, d2, d53);
	or (d53, d46, d54);
	or (d54, d55, d56);
	and (d55, d3, d27);
	or (d56, d39, d57);
	or (d57, d20, d40);
	assign f5 = d58;
	or (d58, d31, d59);
	or (d59, d14, d60);
	or (d60, d46, d61);
	or (d61, d62, d64);
	and (d62, x0, d63);
	and (d63, d5, d16);
	or (d64, d18, d65);
	or (d65, d39, d66);
	or (d66, d20, d41);
	assign f6 = d67;
	or (d67, d68, d69);
	and (d68, d3, d63);
	or (d69, d9, d70);
	or (d70, d14, d71);
	or (d71, d39, d46);
endmodule
