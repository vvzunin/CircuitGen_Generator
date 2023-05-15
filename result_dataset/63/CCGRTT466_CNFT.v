//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT466_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52;

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
	and (d12, d7, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, d8);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, d5, d20);
	and (d20, x2, x3);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d20);
	or (d24, d25, d26);
	and (d25, x0, d11);
	or (d26, d27, d28);
	and (d27, x0, d15);
	or (d28, d29, d31);
	and (d29, x0, d30);
	and (d30, x1, d6);
	or (d31, d32, d34);
	and (d32, x0, d33);
	and (d33, x1, d12);
	and (d34, x0, d35);
	and (d35, x1, d16);
	assign f1 = d36;
	or (d36, d14, d37);
	or (d37, d38, d39);
	and (d38, d3, d30);
	or (d39, d40, d41);
	and (d40, d3, d35);
	or (d41, d42, d43);
	and (d42, x0, d4);
	or (d43, d34, d44);
	and (d44, x0, d19);
	assign f2 = d45;
	or (d45, d10, d46);
	or (d46, d18, d47);
	or (d47, d48, d49);
	and (d48, d3, d33);
	or (d49, d40, d50);
	or (d50, d22, d51);
	or (d51, d29, d52);
	and (d52, x0, d23);
endmodule
