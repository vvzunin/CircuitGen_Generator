//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT479_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55;

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
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, d7, d12);
	or (d21, d22, d24);
	and (d22, d3, d23);
	and (d23, x1, d11);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, d5, d20);
	or (d27, d28, d29);
	and (d28, x0, d10);
	or (d29, d30, d31);
	and (d30, x0, d15);
	or (d31, d32, d33);
	and (d32, x0, d19);
	or (d33, d34, d36);
	and (d34, x0, d35);
	and (d35, x1, d6);
	or (d36, d37, d38);
	and (d37, x0, d23);
	and (d38, x0, d39);
	and (d39, x1, d16);
	assign f1 = d40;
	or (d40, d41, d42);
	and (d41, d3, d26);
	or (d42, d2, d43);
	or (d43, d18, d44);
	or (d44, d22, d45);
	or (d45, d46, d47);
	and (d46, d3, d39);
	or (d47, d25, d48);
	or (d48, d34, d49);
	and (d49, x0, d4);
	assign f2 = d50;
	or (d50, d18, d51);
	or (d51, d46, d52);
	or (d52, d25, d53);
	or (d53, d30, d54);
	or (d54, d32, d55);
	or (d55, d34, d38);
endmodule
