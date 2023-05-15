//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3)
module CCGRTT1850_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d13);
	and (d9, d3, d10);
	and (d10, x1, d11);
	and (d11, x3, d12);
	not (d12, x2);
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d6);
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, x2, x3);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, d7, d12);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, d5, d11);
	or (d27, d28, d30);
	and (d28, x0, d29);
	and (d29, d5, d19);
	and (d30, x0, d18);
	assign f1 = d31;
	or (d31, d32, d33);
	and (d32, d3, d26);
	or (d33, d34, d36);
	and (d34, d3, d35);
	and (d35, x1, d23);
	or (d36, d14, d37);
	or (d37, d21, d38);
	and (d38, x0, d15);
	assign f2 = d39;
	or (d39, d40, d41);
	and (d40, d3, d22);
	or (d41, d32, d42);
	or (d42, d43, d44);
	and (d43, d3, d29);
	or (d44, d34, d45);
	or (d45, d14, d46);
	or (d46, d17, d47);
	or (d47, d21, d48);
	or (d48, d49, d50);
	and (d49, x0, d10);
	or (d50, d30, d38);
	assign f3 = d51;
	or (d51, d40, d52);
	or (d52, d32, d53);
	or (d53, d43, d54);
	or (d54, d34, d55);
	or (d55, d14, d56);
	or (d56, d17, d57);
	or (d57, d49, d58);
	and (d58, x0, d4);
	assign f4 = d59;
	or (d59, d40, d60);
	or (d60, d2, d61);
	or (d61, d50, d62);
	and (d62, x0, d35);
	assign f5 = d63;
	or (d63, d40, d64);
	or (d64, d32, d65);
	or (d65, d43, d66);
	or (d66, d34, d67);
	or (d67, d17, d21);
endmodule
