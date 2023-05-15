//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1786_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61;

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
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d16);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, d7, d12);
	or (d24, d25, d26);
	and (d25, x0, d4);
	or (d26, d27, d28);
	and (d27, x0, d10);
	or (d28, d29, d30);
	and (d29, x0, d15);
	or (d30, d31, d33);
	and (d31, x0, d32);
	and (d32, x1, d23);
	and (d33, x0, d19);
	assign f1 = d34;
	or (d34, d2, d35);
	or (d35, d18, d36);
	or (d36, d25, d37);
	or (d37, d27, d38);
	or (d38, d39, d41);
	and (d39, x0, d40);
	and (d40, x1, d6);
	and (d41, x0, d42);
	and (d42, x1, d11);
	assign f2 = d43;
	or (d43, d44, d45);
	and (d44, d3, d40);
	or (d45, d46, d47);
	and (d46, d3, d42);
	or (d47, d21, d48);
	or (d48, d29, d31);
	assign f3 = d49;
	or (d49, d9, d50);
	or (d50, d14, d51);
	or (d51, d52, d53);
	and (d52, d3, d32);
	or (d53, d46, d54);
	or (d54, d25, d55);
	or (d55, d29, d33);
	assign f4 = d56;
	or (d56, d52, d57);
	or (d57, d44, d58);
	or (d58, d46, d59);
	or (d59, d21, d60);
	or (d60, d25, d61);
	or (d61, d27, d55);
endmodule
