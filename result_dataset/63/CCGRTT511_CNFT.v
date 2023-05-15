//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT511_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69;

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
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, x3, d16);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d23);
	and (d29, x0, d30);
	and (d30, x1, d11);
	assign f1 = d31;
	or (d31, d32, d34);
	and (d32, d3, d33);
	and (d33, d5, d15);
	or (d34, d35, d36);
	and (d35, d3, d22);
	or (d36, d2, d37);
	or (d37, d9, d38);
	or (d38, d39, d40);
	and (d39, d3, d28);
	or (d40, d41, d42);
	and (d41, x0, d33);
	or (d42, d21, d43);
	or (d43, d44, d45);
	and (d44, x0, d10);
	or (d45, d27, d46);
	or (d46, d29, d47);
	and (d47, x0, d19);
	assign f2 = d48;
	or (d48, d32, d49);
	or (d49, d35, d50);
	or (d50, d2, d51);
	or (d51, d39, d52);
	or (d52, d53, d54);
	and (d53, d3, d30);
	or (d54, d41, d46);
	assign f3 = d55;
	or (d55, d2, d56);
	or (d56, d9, d57);
	or (d57, d13, d58);
	or (d58, d18, d59);
	or (d59, d53, d60);
	or (d60, d21, d61);
	or (d61, d26, d62);
	and (d62, x0, d14);
	assign f4 = d63;
	or (d63, d35, d64);
	or (d64, d2, d65);
	or (d65, d13, d66);
	or (d66, d18, d67);
	or (d67, d53, d68);
	or (d68, d41, d69);
	or (d69, d21, d45);
endmodule
