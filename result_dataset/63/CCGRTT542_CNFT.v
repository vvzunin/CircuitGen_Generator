//f0 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT542_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72;

	assign f0 = d1;
	or (d1, d2, d7);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	and (d5, d6, x3);
	not (d6, x2);
	or (d7, d8, d11);
	and (d8, d3, d9);
	and (d9, x1, d10);
	and (d10, x2, x3);
	or (d11, d12, d17);
	and (d12, x0, d13);
	and (d13, d14, d15);
	not (d14, x1);
	and (d15, d6, d16);
	not (d16, x3);
	or (d17, d18, d21);
	and (d18, x0, d19);
	and (d19, d14, d20);
	and (d20, x2, d16);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, d10, d14);
	and (d24, x0, d4);
	assign f1 = d25;
	or (d25, d26, d28);
	and (d26, d3, d27);
	and (d27, d5, d14);
	or (d28, d29, d30);
	and (d29, d3, d19);
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, x1, d15);
	or (d33, d2, d34);
	or (d34, d35, d36);
	and (d35, x0, d27);
	or (d36, d18, d37);
	or (d37, d22, d38);
	or (d38, d39, d40);
	and (d39, x0, d32);
	or (d40, d24, d41);
	and (d41, x0, d9);
	assign f2 = d42;
	or (d42, d29, d43);
	or (d43, d44, d46);
	and (d44, d3, d45);
	and (d45, x1, d20);
	or (d46, d8, d47);
	or (d47, d18, d48);
	or (d48, d22, d49);
	or (d49, d24, d50);
	or (d50, d41, d51);
	and (d51, x0, d45);
	assign f3 = d52;
	or (d52, d53, d54);
	and (d53, d3, d13);
	or (d54, d26, d55);
	or (d55, d31, d56);
	or (d56, d2, d57);
	or (d57, d35, d58);
	or (d58, d18, d49);
	assign f4 = d59;
	or (d59, d53, d60);
	or (d60, d26, d61);
	or (d61, d29, d62);
	or (d62, d44, d63);
	or (d63, d8, d64);
	or (d64, d35, d65);
	or (d65, d22, d66);
	or (d66, d39, d49);
	assign f5 = d67;
	or (d67, d53, d68);
	or (d68, d69, d70);
	and (d69, d3, d23);
	or (d70, d44, d71);
	or (d71, d22, d72);
	or (d72, d39, d51);
endmodule
