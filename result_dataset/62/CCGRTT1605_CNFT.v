//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
module CCGRTT1605_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50;

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
	and (d13, d3, d14);
	and (d14, d5, d15);
	and (d15, x2, x3);
	assign f1 = d16;
	or (d16, d10, d17);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d15);
	or (d23, d24, d25);
	and (d24, x0, d4);
	or (d25, d26, d27);
	and (d26, x0, d14);
	or (d27, d28, d29);
	and (d28, x0, d19);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, x1, d12);
	or (d32, d33, d36);
	and (d33, x0, d34);
	and (d34, x1, d35);
	and (d35, x2, d8);
	and (d36, x0, d22);
	assign f2 = d37;
	or (d37, d38, d40);
	and (d38, d3, d39);
	and (d39, d5, d35);
	or (d40, d41, d42);
	and (d41, d3, d34);
	or (d42, d24, d43);
	or (d43, d26, d44);
	or (d44, d28, d36);
	assign f3 = d45;
	or (d45, d2, d46);
	or (d46, d10, d47);
	or (d47, d13, d48);
	or (d48, d41, d49);
	or (d49, d21, d50);
	or (d50, d26, d30);
endmodule
