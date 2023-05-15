//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1502_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54;

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
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d24);
	and (d21, d3, d22);
	and (d22, x1, d23);
	and (d23, x2, x3);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, d5, d16);
	or (d27, d28, d30);
	and (d28, x0, d29);
	and (d29, d5, d23);
	or (d30, d31, d32);
	and (d31, x0, d19);
	or (d32, d33, d35);
	and (d33, x0, d34);
	and (d34, x1, d11);
	and (d35, x0, d22);
	assign f1 = d36;
	or (d36, d9, d37);
	or (d37, d38, d39);
	and (d38, d3, d29);
	or (d39, d40, d41);
	and (d40, x0, d10);
	or (d41, d28, d42);
	or (d42, d31, d43);
	and (d43, x0, d15);
	assign f2 = d44;
	or (d44, d45, d46);
	and (d45, d3, d26);
	or (d46, d38, d47);
	or (d47, d14, d48);
	or (d48, d49, d50);
	and (d49, d3, d34);
	or (d50, d21, d51);
	or (d51, d25, d52);
	or (d52, d40, d53);
	or (d53, d28, d54);
	or (d54, d31, d33);
endmodule
