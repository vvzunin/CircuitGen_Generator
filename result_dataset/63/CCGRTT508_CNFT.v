//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT508_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57;

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
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d6);
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, x2, x3);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d5, d19);
	or (d23, d24, d25);
	and (d24, x0, d15);
	or (d25, d26, d29);
	and (d26, x0, d27);
	and (d27, x1, d28);
	and (d28, x2, d8);
	and (d29, x0, d18);
	assign f1 = d30;
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d28);
	or (d33, d34, d35);
	and (d34, d3, d22);
	or (d35, d14, d36);
	or (d36, d26, d37);
	and (d37, x0, d11);
	assign f2 = d38;
	or (d38, d10, d39);
	or (d39, d14, d40);
	or (d40, d41, d43);
	and (d41, d3, d42);
	and (d42, x1, d12);
	or (d43, d17, d44);
	or (d44, d37, d45);
	or (d45, d46, d47);
	and (d46, x0, d32);
	or (d47, d21, d26);
	assign f3 = d48;
	or (d48, d34, d49);
	or (d49, d14, d50);
	or (d50, d41, d51);
	or (d51, d52, d53);
	and (d52, d3, d27);
	or (d53, d17, d54);
	or (d54, d55, d56);
	and (d55, x0, d4);
	or (d56, d46, d57);
	or (d57, d21, d25);
endmodule
