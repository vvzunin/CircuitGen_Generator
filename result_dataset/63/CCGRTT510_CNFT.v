//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT510_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60;

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
	and (d11, d5, d12);
	and (d12, x2, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, d8);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d12);
	and (d20, x0, d21);
	and (d21, x1, d6);
	assign f1 = d22;
	or (d22, d23, d26);
	and (d23, d3, d24);
	and (d24, d5, d25);
	and (d25, d7, x3);
	or (d26, d10, d27);
	or (d27, d14, d28);
	or (d28, d29, d30);
	and (d29, x0, d24);
	or (d30, d31, d32);
	and (d31, x0, d11);
	and (d32, x0, d19);
	assign f2 = d33;
	or (d33, d10, d34);
	or (d34, d35, d36);
	and (d35, d3, d21);
	or (d36, d37, d39);
	and (d37, d3, d38);
	and (d38, x1, d25);
	or (d39, d18, d40);
	or (d40, d41, d42);
	and (d41, x0, d4);
	or (d42, d29, d43);
	or (d43, d31, d44);
	or (d44, d32, d45);
	and (d45, x0, d15);
	assign f3 = d46;
	or (d46, d47, d49);
	and (d47, d3, d48);
	and (d48, d5, d16);
	or (d49, d10, d50);
	or (d50, d35, d51);
	or (d51, d37, d52);
	or (d52, d18, d53);
	or (d53, d41, d54);
	or (d54, d29, d55);
	or (d55, d31, d56);
	or (d56, d20, d32);
	assign f4 = d57;
	or (d57, d2, d58);
	or (d58, d23, d59);
	or (d59, d10, d60);
	or (d60, d30, d41);
endmodule
