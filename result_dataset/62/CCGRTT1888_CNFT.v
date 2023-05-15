//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1888_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

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
	and (d10, x1, d11);
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
	or (d21, d22, d23);
	and (d22, x0, d4);
	or (d23, d24, d26);
	and (d24, x0, d25);
	and (d25, d5, d16);
	or (d26, d27, d29);
	and (d27, x0, d28);
	and (d28, x1, d6);
	and (d29, x0, d15);
	assign f1 = d30;
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d11);
	or (d33, d34, d35);
	and (d34, d3, d25);
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, x1, d20);
	or (d38, d9, d39);
	or (d39, d22, d40);
	or (d40, d41, d42);
	and (d41, x0, d37);
	or (d42, d27, d43);
	or (d43, d29, d44);
	and (d44, x0, d10);
	assign f2 = d45;
	or (d45, d46, d47);
	and (d46, d3, d19);
	or (d47, d31, d48);
	or (d48, d9, d49);
	or (d49, d18, d50);
	or (d50, d24, d51);
	or (d51, d41, d44);
	assign f3 = d52;
	or (d52, d46, d53);
	or (d53, d54, d55);
	and (d54, d3, d28);
	or (d55, d14, d56);
	or (d56, d22, d57);
	or (d57, d24, d58);
	or (d58, d41, d59);
	or (d59, d27, d44);
	assign f4 = d60;
	or (d60, d54, d61);
	or (d61, d22, d59);
	assign f5 = d62;
	or (d62, d2, d63);
	or (d63, d54, d64);
	or (d64, d9, d65);
	or (d65, d14, d66);
	or (d66, d22, d58);
endmodule
